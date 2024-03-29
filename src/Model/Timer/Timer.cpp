/**
 * @file Timer.cpp
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

#include "Timer.h"
#include <boost/thread/thread.hpp>
#include <iostream>
#include <cassert>
#include "../../../lib/StaticLog/StaticLog.h"

Timer::Timer()
{
    timeSlice = 1000; //Default: wait 1 second per time-slice
    finalTime = 25;
    clock = 0;
}

Timer::Timer
    (
        unsigned int timeSliceToSet,
        unsigned int finalTimeToSet
    )
    :
    timeSlice(timeSliceToSet),
    finalTime(finalTimeToSet)
{
    clock = 0;
}

Timer::~Timer(){}

unsigned int Timer::getTimeSlice()
{
    return timeSlice;
}

unsigned int Timer::getFinalTime()
{
    return finalTime;
}

unsigned int Timer::getCurrentTime()
{
    return clock;
}

void Timer::setTimeSlice(unsigned int timeSliceToSet)
{
    timeSlice = timeSliceToSet;
}

void Timer::setFinalTime(unsigned int finalTimeToSet)
{
    finalTime = finalTimeToSet;
}

void Timer::start()
{
    assert(StaticLog::log["general"] != NULL);
    std::ostream* log = StaticLog::log["general"];
    //assert(StaticLog::log["xml"] != NULL); TODO XML OUTPUT
    //std::ostream* xml = StaticLog::log["xml"]; TODO XML OUTPUT
    for(; clock != finalTime; clock++)
    {
        (*log) << std::endl << std::endl;
        (*log) << "Current time: " << clock << std::endl;
        notify();
        (*log) << "\t-----------------------------------------------" << std::endl;
    }
}

void Timer::reset()
{
    clock = 0;
}
