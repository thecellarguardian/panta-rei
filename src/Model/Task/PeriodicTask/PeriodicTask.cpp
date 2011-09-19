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

PeriodicTask::PeriodicTask
    (
        const int taskIDToSet,
        const int arrivalTimeToSet,
        const int computationTimeToSet,
        const int relativeDeadlineToSet,
        const int periodToSet
    )
    :
    Task
    (
        taskIDToSet,
        arrivalTimeToSet,
        computationTimeToSet,
        relativeDeadlineToSet
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
    elapsedTime++;
    instantaneousExceedingTime =
        (elapsedTime > relativeDeadline)?
        elapsedTime - relativeDeadline : 0;
    remainingComputationTime =
        (currentState == EXECUTING)?
        remainingComputationTime - 1 : remainingComputationTime;
    remainingPeriod--;
}


void PeriodicTask::reset()
{
    currentInstanceArrivalTime += period;
    elapsedTime = 0;
    remainingComputationTime = computationTime;
    instantaneousExceedingTime = 0;
}
