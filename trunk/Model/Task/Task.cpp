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
        const int arrivalTimeToSet,
        const int computationTimeToSet,
        const int relativeDeadlineToSet
    )
    :
    arrivalTime(arrivalTimeToSet),
    computationTime(computationTimeToSet),
    relativeDeadline(relativeDeadlineToSet),
    absoluteDeadline(arrivalTimeToSet + relativeDeadlineToSet),
    elapsedTime(0),
    instantaneousExceedingTime(0)
    {}
    
int Task::getArrivalTime()
{
    return arrivalTime;
}

int Task::getComputationTime()
{
    return computationTime;
}

int Task::getRelativeDeadline()
{
    return relativeDeadline;
}

int Task::getAbsoluteDeadline()
{
    return absoluteDeadline;
}

int Task::getElapsedTime()
{
    return elapsedTime;
}

int Task::getInstantaneousExceedingTime()
{
    return instantaneousExceedingTime;
}

bool deadlineMiss()
{
    return instantaneousExceedingTime > 0;
}
