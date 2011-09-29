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

#include "Task.h"

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
    instantaneousExceedingTime(0),
    remainingComputationTime(computationTimeToSet),
    currentState(EXECUTING),
    timer(timerToSet)
{
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

bool Task::deadlineMiss()
{
    return instantaneousExceedingTime > 0;
}

void Task::setState(TaskState stateToSet)
{
    currentState = stateToSet;
}

TaskState Task::getState()
{
    return currentState;
}
