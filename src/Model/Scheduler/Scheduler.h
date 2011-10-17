/**
 * @file Scheduler.h
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

#include "../../../lib/DesignPatterns/Observer/Observer.h"
#include "../../../lib/Queue/QueueInterface/QueueInterface.h"
#include "../SystemQueuesManager/SystemQueuesManager.h"
#include "../Task/Task.h"
#include "../Timer/Timer.h"
#include <boost/shared_ptr.hpp>

#ifndef SCHEDULER_H
#define SCHEDULER_H

/**
 * @class Scheduler
 * @brief A task manager for task activation.
 * An Scheduler is a Timer observer. It has references to the ready and the
 * execution queue. In particular, it owns those queues, so it has to provide
 * proper implementations for their QueueInterfaces, which are obtained through
 * the queue naming system. When a scheduler is updated, a scheduling step is
 * done according to the particular scheduling policy implemented. Particular
 * scheduling policies are defined by mean of inheritance, through the
 * definition of the update method.
 **/
class Scheduler : public Observer
{
    protected:
        bool preemptionActivated;
        /**< This flag indicates if the scheduler is preemptive. **/
        boost::shared_ptr<SystemQueuesManager> systemQueues;
        /**< Shared pointer to the queue naming system. **/
        boost::shared_ptr< QueueInterface<Task> > readyQueue;
        /**< Shared pointer to the ready queue. **/
        boost::shared_ptr< QueueInterface<Task> > executionQueue;
        /**< Shared pointer to the execution queue. **/
        Timer* timer;
        /**<
         * Pointer to the Timer. A normal pointer is used, due to avoid
         * the shared pointer circular reference problem.
         **/
    public:
        Scheduler
            (
                bool preemptiveFlag,
                boost::shared_ptr<SystemQueuesManager> systemQueuesToSet,
                Timer* timerToSet
            );
        virtual ~Scheduler();
};

#endif
