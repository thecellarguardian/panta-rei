/**
 * @file Activator.cpp
 * @author Cosimo Sacco <cosimosacco@gmail.com>
 *
 * @section LICENSE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include "Activator.h"
#include "../../../lib/Queue/Implementations/OrderedQueueImplementation/OrderedQueueImplementation.h"
#include "../../../lib/Queue/Implementations/FIFOQueueImplementation/FIFOQueueImplementation.h"
#include "../SchedulationEvents/VisitableSchedulingEvent.h"

bool ArrivalTimeComparator::operator()
    (boost::shared_ptr<Task>& a, boost::shared_ptr<Task>& b)
{
    return
        (
            a->getCurrentInstanceArrivalTime() <
            b->getCurrentInstanceArrivalTime()
        );
}

Activator::Activator
    (
        boost::shared_ptr<SystemQueuesManager> systemQueuesToSet,
        Timer* timerToSet
    )
    : systemQueues(systemQueuesToSet), timer(timerToSet)
{
    timer->attach(this);
    activationQueue = (*systemQueues)["activation"];
    readyQueue = (*systemQueues)["ready"];
    activationQueue->setImplementation
        (queueImplementationProvider.getImplementation());
    //TODO
    //<reduntant code to refactor>
    boost::shared_ptr
        <
        FIFOQueueImplementation
            <
            Event
                <
                unsigned int,
                unsigned int
                >
            >
        >
        implementation
        (
            new FIFOQueueImplementation
            <
            Event
                <
                unsigned int,
                unsigned int
                >
            >
        );
    setImplementation(implementation);
    //</reduntant code to refactor>
}

Activator::~Activator(){}

void Activator::update(Subject* subject)
{
    if(activationQueue->size() == 0)
    {
        std::cout << "The activation queue is empty" << std::endl;
        return;
    }
    while
        (
            (activationQueue->size() > 0)
            &&
            (activationQueue->front())->getCurrentInstanceArrivalTime() ==
            timer->getCurrentTime()
        )
    {
        std::cout << "A task is being activated" << std::endl;
        boost::shared_ptr<Task> taskToActivate = activationQueue->extract();
        std::cout << "The task to activate is: " <<
            taskToActivate->getTaskID() << std::endl;
        taskToActivate->setState(READY);
        std::cout << "ACTIVATOR: publishing arrival event" << std::endl;
        publishArrivalEvent(taskToActivate->getTaskID());
        readyQueue->insert(taskToActivate);
        notify();
    }
}

void Activator::registerForActivation(boost::shared_ptr<Task> taskToRegister)
{
    if
        (
            timer->getCurrentTime() >=
            taskToRegister->getCurrentInstanceArrivalTime()
        )
    {
        std::cout << "Task" << taskToRegister->getTaskID() <<
            " is being insert in the ready queue" << std::endl;
        taskToRegister->setState(READY);
        publishArrivalEvent(taskToRegister->getTaskID());
        readyQueue->insert(taskToRegister);
        notify();
    }
    else
    {
        std::cout << "Task" << taskToRegister->getTaskID() <<
            " is being enqueued for activation" << std::endl;
        activationQueue->insert(taskToRegister);
    }
}

void Activator::publishArrivalEvent(unsigned int taskID)
{
    boost::shared_ptr< Event<unsigned int, unsigned int> > newEvent
        (
            static_cast< Event<unsigned int, unsigned int>* >
            (
                new VisitableSchedulingEvent<ARRIVAL>
                (taskID, timer->getCurrentTime())
            )
        );
    insert(newEvent);
}

void Activator::print()
{
    activationQueue->print();
}
