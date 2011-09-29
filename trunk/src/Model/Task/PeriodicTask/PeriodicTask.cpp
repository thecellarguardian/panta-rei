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

/* To disable assertions:
 * #ifndef NDEBUG
 * #define NDEBUG
 * #endif
 */

#include "PeriodicTask.h"
#include <cassert>
#include <iostream> //TODO remove this

PeriodicTask::PeriodicTask
    (
        const unsigned int taskIDToSet,
        const unsigned int arrivalTimeToSet,
        const unsigned int computationTimeToSet,
        const unsigned int relativeDeadlineToSet,
        const unsigned int periodToSet,
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
    period
        (
            (
                (periodToSet >= relativeDeadline)?
                periodToSet : relativeDeadline
            )
        ),
    currentInstanceArrivalTime(arrivalTimeToSet)
    {
        remainingPeriod = period;
    }

PeriodicTask::~PeriodicTask(){}

unsigned int PeriodicTask::getCurrentInstanceArrivalTime()
{
    return currentInstanceArrivalTime;
}

int PeriodicTask::getRemainingPeriod()
{
    return remainingPeriod;
}

void PeriodicTask::update()
{
    print();
    //AUTOMATA BASED MODEL
    switch(currentState)
    {
        case NEW:
        {
            assert(timer->getCurrentTime() < arrivalTime);
            break;
        }
        case READY:
        {
            assert(timer->getCurrentTime() >= arrivalTime);
            elapsedTime++;
            instantaneousExceedingTime =
                (elapsedTime > relativeDeadline)?
                elapsedTime - relativeDeadline : 0;
            remainingPeriod--;
            break;
        }
        case EXECUTING:
        {
            assert(timer->getCurrentTime() >= arrivalTime);
            elapsedTime++;
            instantaneousExceedingTime =
                (elapsedTime > relativeDeadline)?
                elapsedTime - relativeDeadline : 0;
            remainingComputationTime--;
            remainingPeriod--;
        }
        case SUSPENDED:
        {
            assert(remainingComputationTime == 0 && remainingPeriod > 0);
            elapsedTime++;
            remainingPeriod--;
        }
    }
    /*if(timer->getCurrentTime() >= arrivalTime)
    {
        elapsedTime++;
        instantaneousExceedingTime =
            (elapsedTime > relativeDeadline)?
            elapsedTime - relativeDeadline : 0;
        remainingComputationTime =
            (currentState == EXECUTING && remainingComputationTime > 0)?
            remainingComputationTime - 1 : remainingComputationTime;
        remainingPeriod--;
    }*/
}


void PeriodicTask::reset()
{
    unsigned int activityInterval =
        timer->getCurrentTime() - currentInstanceArrivalTime;
    //Next arrival time: (ceiling((now - arrival)/period))*period
    currentInstanceArrivalTime +=
        (
            (activityInterval/period) +
            ((activityInterval%period == 0)? 0 : 1)
        )*period;
    elapsedTime = 0;
    absoluteDeadline = currentInstanceArrivalTime + relativeDeadline;
    remainingComputationTime = computationTime;
    instantaneousExceedingTime = 0;
}

void PeriodicTask::print()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "TaskID: " << getTaskID() <<
    ((timer->getCurrentTime() == getCurrentInstanceArrivalTime())? " ACTIVATED" : "")
    << std::endl;
    std::cout << "Computation time left: " << getRemainingComputationTime()
    << std::endl;
    std::cout << "Elapsed time: " << getElapsedTime() << std::endl;
    std::cout << "Instantaneous exceeding time: " <<
    getInstantaneousExceedingTime() << std::endl;
    std::cout << ((deadlineMiss())? "DEADLINE MISS!" : "") << std::endl;
}
