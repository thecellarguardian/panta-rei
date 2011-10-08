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
}

Activator::~Activator(){}

void Activator::update()
{
    if(activationQueue->size() == 0)
    {
        std::cout << "The activation queue is empty" << std::endl;
        return;
    }
    if
        (
            (activationQueue->front())->getCurrentInstanceArrivalTime() ==
            timer->getCurrentTime()
        )
    {
        std::cout << "A task is being activated" << std::endl;
        boost::shared_ptr<Task> taskToActivate = activationQueue->extract();
        std::cout << "The task to activate is: " <<
            taskToActivate->getTaskID() << std::endl;
        taskToActivate->setState(READY);
        readyQueue->insert(taskToActivate);
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
        readyQueue->insert(taskToRegister);
    }
    else
    {
        std::cout << "Task" << taskToRegister->getTaskID() <<
            " is being enqueued for activation" << std::endl;
        activationQueue->insert(taskToRegister);
    }
}

void Activator::print()
{
    activationQueue->print();
}
