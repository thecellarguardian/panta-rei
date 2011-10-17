/**
 * @file Timer.h
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

#include "../../../lib/DesignPatterns/Observer/Subject.h"

#ifndef TIMER_H
#define TIMER_H

/**
 * @class Timer
 * @brief This class models a real-time timer.
 * A timer is a producer of time events. It is set to an initial value, and when
 * activated he notifies the end of a time slice to its state observers.
 * Notice that this is a simulation of a real-time system on a non real-time
 * machine, thus this timer is not granted neither to generate exact
 * temporization nor to meet real-time costraints.
 * A timer is initialized with its starting and final time; it simply cycles
 * (finalTime - startingTime) times and, every time, it notifies its observers.
 * If the online flag is set, every notification is preceded by a pause of
 * timeSlice milliseconds.
 **/
class Timer : public Subject
{
    private:
        unsigned int timeSlice;
        unsigned int finalTime;
        unsigned int clock;
    public:
        Timer();
        Timer
        (
            unsigned int timeSliceToSet,
            unsigned int finalTimeToSet
        );
        virtual ~Timer();
        unsigned int getTimeSlice();
        unsigned int getFinalTime();
        unsigned int getCurrentTime();
        void setFinalTime(unsigned int finalTimeToSet);
        void setTimeSlice(unsigned int timeSliceToSet);
        /**
         * Starts the Timer. For finalTime times the timer updates its observers
         * and then waits for timeSlice ms.
         **/
        void start();
};

#endif
