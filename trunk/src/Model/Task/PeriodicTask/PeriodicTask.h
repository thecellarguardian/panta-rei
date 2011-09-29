/**
 * @file PeriodicTask.h
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

#include "../Task.h"

#ifndef PERIODIC_TASK_H
#define PERIODIC_TASK_H

/**
 * @class PeriodicTask
 * @brief This class models a periodic task.
 * A periodic task is a task with an additional micro-state dimension,
 * the period, which has to be reactivated at the end of each period. If a
 * period-miss happens, the task must be reactivated when the next period
 * available starts (some periods may be lost).
 **/
class PeriodicTask : public Task
{
    private:
        const unsigned int period;
        unsigned int currentInstanceArrivalTime;
        int remainingPeriod; //Notice: it can be < 0 in case of period miss
    protected:
    public:
        PeriodicTask
        (
            const unsigned int taskID,
            const unsigned int arrivalTime,
            const unsigned int computationTime,
            const unsigned int relativeDeadline,
            const unsigned int period,
            Timer* timer
        );
    unsigned int getCurrentInstanceArrivalTime();
    int getRemainingPeriod();
    void update();
    void reset();
    void print();
};

#endif
