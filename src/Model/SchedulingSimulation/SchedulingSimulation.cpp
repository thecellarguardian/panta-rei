/**
 * @file SchedulingSimulation.cpp
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

#include "SchedulingSimulation.h"
#include "../Task/PeriodicTask/PeriodicTask.h"
#include "../Scheduler/RateMonotonic/RateMonotonic.h"
#include "../Scheduler/EarliestDeadlineFirst/EarliestDeadlineFirst.h"
#include <cassert>
#include <iostream>

SchedulingSimulation::SchedulingSimulation()
    :
    timer(1, 25),
    systemQueues(new SystemQueuesManager()),
    activator(new Activator(systemQueues, &timer)), //No initialization issues
    scheduler(new RateMonotonic(true,systemQueues, &timer,activator)),
    taskIDGenerator(1),
    simulationDone(false)
{}

SchedulingSimulation::SchedulingSimulation
(
    int simulationLength,
    boost::shared_ptr<Scheduler> schedulerToSet
)
    :
    timer(1, simulationLength) ,
    systemQueues(new SystemQueuesManager()),
    activator(new Activator(systemQueues, &timer)), //No initialization issues
    scheduler(schedulerToSet),
    taskIDGenerator(1),
    simulationDone(false)
{}

unsigned int SchedulingSimulation::createPeriodicTask
(
    unsigned int arrivalTime,
    unsigned int computationTime,
    unsigned int relativeDeadline,
    unsigned int period
)
{
    boost::shared_ptr<Task> newPeriodicTask
        (
            new PeriodicTask
                (
                    taskIDGenerator,
                    arrivalTime,
                    computationTime,
                    relativeDeadline,
                    period,
                    &timer
                )
        );
    tasks.push_back(newPeriodicTask);
    taskIDGenerator++;
    //If, after the increment, taskIDGenerator is 0, an overflow happened
    assert(taskIDGenerator != 0);
    std::cout << "New periodic task created" << std::endl;
    std::cout << "arrival time: " << arrivalTime << std::endl;
    std::cout << "computation time: " << computationTime << std::endl;
    std::cout << "relative deadline: " << relativeDeadline << std::endl;
    std::cout << "period: " << period << std::endl;
}

//TODO void removeTask(unsigned int taskID)??

void SchedulingSimulation::setSimulationLength(unsigned int simulationLengthToSet)
{
    timer.setFinalTime(simulationLengthToSet);
}

void SchedulingSimulation::simulate()
{
    if(!simulationDone)
    {
        assert(scheduler.get() != NULL);
        std::cout << "SIMULATION BEGIN" << std::endl;
        std::cout << "scheduler: " << (void*)scheduler.get() << std::endl;
        history.registerToEventSource(activator.get());
        history.registerToEventSource(scheduler.get());
        for
            (
                std::list< boost::shared_ptr<Task> >::iterator i = tasks.begin();
                i != tasks.end();
                i++
            )
        {
            history.registerToEventSource((*i).get());
        }
        for
            (
                std::list< boost::shared_ptr<Task> >::iterator i = tasks.begin();
                i != tasks.end();
                i++
            )
        {
            activator->registerForActivation(*i);
        }
        timer.start();
        timer.reset();
        simulationDone = true;
    }
}

void SchedulingSimulation::clear()
{
    timer.reset();
    timer.detachAll();
    timer.setFinalTime(25);
    boost::shared_ptr<SystemQueuesManager>
        newSystemQueues(new SystemQueuesManager());
    systemQueues = newSystemQueues;
    boost::shared_ptr<Activator>
        newActivator(new Activator(systemQueues, &timer));
    activator = newActivator;
    boost::shared_ptr<Scheduler>
        newScheduler(new RateMonotonic(true,systemQueues, &timer,activator));
    scheduler = newScheduler;
    tasks.erase(tasks.begin(), tasks.end());
    history.clear();
    taskIDGenerator = 1;
    simulationDone = false;
}

void SchedulingSimulation::accept(Visitor* visitor)
{
    history.accept(visitor);
}
