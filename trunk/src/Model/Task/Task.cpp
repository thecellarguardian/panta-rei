/**
 * @file Task.cpp
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
 *
 */

#include <iostream>
#include "Task.h"
#include "../SchedulationEvents/VisitableSchedulingEvent.h"
#include "../../../lib/Queue/Implementations/FIFOQueueImplementation/FIFOQueueImplementation.h"

Task::Task
    (
        const unsigned int taskIDToSet,
        const unsigned int arrivalTimeToSet,
        const unsigned int computationTimeToSet,
        const unsigned int relativeDeadlineToSet,
        Timer* timerToSet
    )
    :
    taskID(taskIDToSet),
    arrivalTime(arrivalTimeToSet),
    computationTime(computationTimeToSet),
    relativeDeadline
        (
            (
                (relativeDeadlineToSet >= computationTimeToSet)?
                relativeDeadlineToSet : computationTimeToSet
            )
        ),
    elapsedTime(0),
    remainingComputationTime(computationTimeToSet),
    instantaneousExceedingTime(0),
    pendingInstances(1),
    currentState(NEW),
    timer(timerToSet)
{
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
    absoluteDeadline = arrivalTimeToSet + relativeDeadlineToSet;
    timer->attach(this);
}

Task::~Task(){}

unsigned int Task::getTaskID()
{
    return taskID;
}

unsigned int Task::getComputationTime()
{
    return computationTime;
}

unsigned int Task::getRemainingComputationTime()
{
    return remainingComputationTime;
}

unsigned int Task::getRelativeDeadline()
{
    return relativeDeadline;
}

unsigned int Task::getAbsoluteDeadline()
{
    std::cout << "Task" << taskID << "has absolute deadline: " << absoluteDeadline << std::endl;
    return absoluteDeadline;
}

unsigned int Task::getElapsedTime()
{
    return elapsedTime;
}

unsigned int Task::getInstantaneousExceedingTime()
{
    return instantaneousExceedingTime;
}

unsigned int Task::getPendingInstances()
{
    return pendingInstances;
}

bool Task::deadlineMiss()
{
    return
        (
            (remainingComputationTime > 0)
            &&
            (timer->getCurrentTime() >= getAbsoluteDeadline())
        );
}

void Task::setState(TaskState stateToSet)
{
    currentState = stateToSet;
}

TaskState Task::getState()
{
    return currentState;
}

void Task::publishEvent(SchedulingEventType typeOfEvent)
{
    boost::shared_ptr< Event<unsigned int, unsigned int> > newEvent
        (
            (typeOfEvent == ARRIVAL)?
                static_cast< Event<unsigned int, unsigned int>* >
                (
                    new VisitableSchedulingEvent<ARRIVAL>
                    (taskID, timer->getCurrentTime())
                )
                :
            (typeOfEvent == PENDING_ARRIVAL)?
                static_cast< Event<unsigned int, unsigned int>* >
                (
                    new VisitableSchedulingEvent<PENDING_ARRIVAL>
                    (taskID, timer->getCurrentTime() + 1)
                )
                :
            (typeOfEvent == END_OF_COMPUTATION)?
                static_cast< Event<unsigned int, unsigned int>* >
                (
                    new VisitableSchedulingEvent<END_OF_COMPUTATION>
                    (taskID, timer->getCurrentTime() + 1)
                )
                :
                static_cast< Event<unsigned int, unsigned int>* >
                (
                    new VisitableSchedulingEvent<DEADLINE_MISS>
                    (taskID, timer->getCurrentTime())
                )
        );
    insert(newEvent);
}
