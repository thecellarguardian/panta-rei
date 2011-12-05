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
#include <cassert>
#include <iostream>

SchedulingSimulation::SchedulingSimulation()
    :
    timer(1, 25),
    systemQueues(new SystemQueuesManager()),
    activator(new Activator(systemQueues, &timer)), //No initialization issues
    taskIDGenerator(1)
{
    std::cout << "SchedulingSimulation::SchedulingSimulation()" << std::endl;
    setSchedulingAlgorithm<RateMonotonic>(true);
}

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
    taskIDGenerator(1)
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
}

//TODO void removeTask(unsigned int taskID)??

void SchedulingSimulation::setSimulationLength(unsigned int simulationLengthToSet)
{
    timer.setFinalTime(simulationLengthToSet);
}

void SchedulingSimulation::simulate()
{
    assert(scheduler.get() != NULL);
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
}

void SchedulingSimulation::accept(Visitor* visitor)
{
    history.accept(visitor);
}
