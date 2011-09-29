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
#include <ostream>

#ifndef TASK_H
#define TASK_H

enum TaskState
{
    NEW,
    READY,
    EXECUTING,
    SUSPENDED
};

/**
 * @class Task
 * @brief This class models a generic task.
 * The data part of a Task object models the task state, while the update method
 * modifies the state according in function of the present state. In particular,
 * we can define:
 * - a macro-state: indicates the "functioning modality" of the task;
 * - a micro-state: the micro state defines the nuances into the macro-state;
 *
 * Here it is an exemple: a task could be READY (macro-state) to be scheduled,
 * but its instantaneous exceeding time could be greater than zero (part of the
 * micro-state which indicates, in this case, that a deadline-miss happened).
 * The macro-state of a task is set by a task manager, such as a scheduler or an
 * acrivator, and it's like a "modality switch"; the task reacts to a time
 * event in different ways according to its current macro-state. Each task is
 * a Timer observer, and each time event triggers the micro-state update, while
 * the macro-state is set by a task manager.
 **/
class Task : public Observer
{
    protected:
        const unsigned int taskID; /**< It must be univocal for each task.**/
        const unsigned int arrivalTime;
        const unsigned int computationTime;
        const unsigned int relativeDeadline;
        unsigned int absoluteDeadline;
        unsigned int elapsedTime; /**< Time elapsed since activation.**/
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
    virtual ~Task();
    unsigned int getTaskID();
    /**
     * This method returns the current task instance arrival time. The method
     * is virtual pure since the returned quantity changes with the
     * particular task type. An exemple: for aperiodic tasks, the returned
     * value is arrivalTime, since there's only one instance of the task.
     * Concerning periodic tasks, the arrival time of the current instance (be
     * it the k-th) is arrivalTime + k*period.
     * @return Current task instance arrival time.
     **/
    virtual unsigned int getCurrentInstanceArrivalTime() = 0;
    unsigned int getComputationTime();
    unsigned int getRemainingComputationTime();
    unsigned int getRelativeDeadline();
    unsigned int getAbsoluteDeadline();
    unsigned int getElapsedTime();
    unsigned int getInstantaneousExceedingTime();
    /**
     * It returns true if the instantaneousExceedingTime is greater than 0.
     * @return True if there has been a deadline miss.
     **/
    bool deadlineMiss();
    /**
     * This method is called by a task manager, such as the scheduler or the
     * activator. It triggers a macro-state transition (which, in this case,
     * happen not to have related actions).
     **/
    void setState(TaskState stateToSet);
    TaskState getState();
    virtual void update() = 0;
    virtual void print() = 0;
};

#endif
