/**
 * @file PeriodicTask.cpp
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

#include "PeriodicTask.h"
#include <iostream> //TODO remove this

PeriodicTask::PeriodicTask
    (
        const int taskIDToSet,
        const int arrivalTimeToSet,
        const int computationTimeToSet,
        const int relativeDeadlineToSet,
        const int periodToSet,
        Timer* timerToSet
    )
    :
    Task
    (
        taskIDToSet,
        arrivalTimeToSet,
        computationTimeToSet,
        relativeDeadlineToSet,
        timerToSet
    ),
    period(periodToSet),
    currentInstanceArrivalTime(0),
    remainingPeriod(periodToSet)
    {}

int PeriodicTask::getCurrentInstanceArrivalTime()
{
    return currentInstanceArrivalTime;
}

int PeriodicTask::getRemainingPeriod()
{
    return remainingPeriod;
}

void PeriodicTask::update()
{
    testPrint();
    if(timer->getCurrentTime() >= arrivalTime)
    {
        elapsedTime++;
        instantaneousExceedingTime =
            (elapsedTime > relativeDeadline)?
            elapsedTime - relativeDeadline : 0;
        remainingComputationTime =
            (currentState == EXECUTING)?
            remainingComputationTime - 1 : remainingComputationTime;
        remainingPeriod--;
    }
}


void PeriodicTask::reset()
{
    currentInstanceArrivalTime += period;
    elapsedTime = 0;
    remainingComputationTime = computationTime;
    instantaneousExceedingTime = 0;
}

void PeriodicTask::testPrint()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "TaskID: " << getTaskID() <<
    ((timer->getCurrentTime() == getArrivalTime())? " ACTIVATED" : "")
    << std::endl;
    std::cout << "Computation time left: " << getComputationTime() << std::endl;
    std::cout << "Elapsed time: " << getElapsedTime() << std::endl;
    std::cout << "Instantaneous exceeding time: " <<
    getInstantaneousExceedingTime() << std::endl;
    std::cout << ((deadlineMiss())? "DEADLINE MISS!" : "") << std::endl;
}
