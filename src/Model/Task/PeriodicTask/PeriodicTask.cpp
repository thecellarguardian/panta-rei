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

unsigned int PeriodicTask::getPeriod()
{
    return period;
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
            assert(timer->getCurrentTime() < getCurrentInstanceArrivalTime());
            break;
        }
        case READY:
        {
            assert(timer->getCurrentTime() >= getCurrentInstanceArrivalTime());
            elapsedTime++;
            instantaneousExceedingTime =
                (elapsedTime > relativeDeadline)?
                elapsedTime - relativeDeadline : 0;
            remainingPeriod--;
            if((elapsedTime % period) == 0)
            {
                pendingInstances++;
            }
            break;
        }
        case EXECUTING:
        {
            assert(timer->getCurrentTime() >= getCurrentInstanceArrivalTime());
            elapsedTime++;
            instantaneousExceedingTime =
                (elapsedTime > relativeDeadline)?
                elapsedTime - relativeDeadline : 0;
            remainingComputationTime--;
            remainingPeriod--;
            if((elapsedTime % period) == 0)
            {
                pendingInstances++;
            }
            if(remainingComputationTime == 0)
            {
                pendingInstances--;
            }
            break;
        }
    }
}

//Precondition: the task has terminated its execution right now
void PeriodicTask::reset()
{
    currentInstanceArrivalTime += period;
    elapsedTime =
        (timer->getCurrentTime() <= currentInstanceArrivalTime)?
        0 : timer->getCurrentTime() - currentInstanceArrivalTime;
    absoluteDeadline += period;
    remainingComputationTime = computationTime;
    remainingPeriod =
        (pendingInstances > 0)?
        period - ((timer->getCurrentTime() - arrivalTime) % period)
        : period;
    if(pendingInstances == 0) {pendingInstances++;}
    instantaneousExceedingTime =
        (timer->getCurrentTime() > absoluteDeadline)?
        (timer->getCurrentTime() - absoluteDeadline) : 0;
    currentState = NEW;
}

void PeriodicTask::print()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "TaskID: " << getTaskID() <<
        (
            (timer->getCurrentTime() == getCurrentInstanceArrivalTime())?
            " ACTIVATED" : ""
        )
    << std::endl;
    std::cout <<
        (
            (currentState == NEW)? "NEW" :
            (currentState == READY)? "READY" :
            (currentState == EXECUTING)? "EXECUTING" : "UNKNOWN STATE!"
        ) << std::endl;
    std::cout << "Current instance arrival time: " <<
        getCurrentInstanceArrivalTime() << std::endl;
    std::cout << "Computation time left: " << getRemainingComputationTime()
    << std::endl;
    std::cout << "Elapsed time: " << getElapsedTime() << std::endl;
    std::cout << "Instantaneous exceeding time: " <<
    getInstantaneousExceedingTime() << std::endl;
    std::cout << "Pending instances: " << getPendingInstances() << std::endl;
    std::cout << ((deadlineMiss())? "DEADLINE MISS!" : "") << std::endl;
}
