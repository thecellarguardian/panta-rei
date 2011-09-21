/**
 * @file Task.h
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

#include "../../../lib/DesignPatterns/Observer/Observer.h"
#include "../Timer/Timer.h"

#ifndef TASK_H
#define TASK_H

enum TaskState
{
    NEW,
    READY,
    EXECUTING,
    SUSPENDED
};

class Task : public Observer
{
    protected:
        const unsigned int taskID;
        const unsigned int arrivalTime;
        const unsigned int computationTime;
        const unsigned int relativeDeadline;
        unsigned int absoluteDeadline;
        unsigned int elapsedTime;
        unsigned int remainingComputationTime;
        unsigned int instantaneousExceedingTime;
        TaskState currentState;
        Timer* timer;
    protected:
    public:
    Task
    (
        const unsigned int taskIDToSet,
        const unsigned int arrivalTimeToSet,
        const unsigned int computationTimeToSet,
        const unsigned int relativeDeadlineToSet,
        Timer* timer
    );
    unsigned int getTaskID();
    unsigned int getArrivalTime();
    unsigned int getComputationTime();
    unsigned int getRemainingComputationTime();
    unsigned int getRelativeDeadline();
    unsigned int getAbsoluteDeadline();
    unsigned int getElapsedTime();
    unsigned int getInstantaneousExceedingTime();
    bool deadlineMiss();
    void setState(TaskState stateToSet);
    TaskState getState();
    virtual void update() = 0;
};

#endif
