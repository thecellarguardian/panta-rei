/**
 * @file DeadlineMonotonic.h
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

#include <boost/shared_ptr.hpp>
#include <cassert>
#include "../Scheduler.h"
#include "../../../../lib/StaticLog/StaticLog.h"
#include "../../../../lib/Queue/QueueImplementationProvider/QueueImplementationProvider.h"
#include "../../../../lib/Queue/Implementations/OrderedQueueImplementation/OrderedQueueImplementation.h"
#include "../../../../lib/Queue/Implementations/SingleSlotQueueImplementation/SingleSlotQueueImplementation.h"
#include "../../SchedulationEvents/VisitableSchedulingEvent.h"
#include "../../Activator/Activator.h"
#include "../../Task/Task.h"

#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

/**
 * @class PriorityScheduler
 * @brief Generic scheduler with priority check.
 * A PriorityScheduler implements a generic scheduler based on priorities. The
 * priority law (the law that states when a task has priority over another task)
 * is provided through the template parameter PriorityComparator.
 * The implementation is based on the concept of decision tree.
 * @tparam PriorityComparator This parameter refers a functor class whose
 * operator() takes two boost::shared_ptr<Task> and returns true if the first
 * parameter has priority over the second. The use of different comparators
 * lets the programmer bind this generic priority based scheduler to particular
 * priority policies.
 **/
//TODO Use Boost Concept Check Library!
template <typename PriorityComparator>class PriorityScheduler
    : public Scheduler
{
    private:
        PriorityComparator comparator;
        QueueImplementationProvider
            <OrderedQueueImplementation< Task, PriorityComparator> >
            readyQueueImplementationProvider;
        /**<
         * This member provides the ready queue implementation. A ordered
         * priority queue is a good choice.
         **/
        QueueImplementationProvider< SingleSlotQueueImplementation<Task> >
            executionQueueImplementationProvider;
        /**<
         * This member provides the execution queue implementation. Since our
         * simulation is concerned in single CPU systems, the best
         * implementation for the execution queue is a SingleSlotQueue.
         **/
         /**
          * Scheduling decision: the task in the execution queue is reactivated
          * and rescheduled at once.
          **/
        void reExecute()
        {
            (executionQueue->front())->reset();
            (executionQueue->front())->setState(EXECUTING);
            publishEvent((executionQueue->front())->getTaskID(), SCHEDULE);
        }
        /**
         * Scheduling decision: the executing task is reactivated.
         **/
        void reActivate()
        {
            (executionQueue->front())->reset();
            activator->registerForActivation(executionQueue->extract());
        }
        /**
         * Scheduling decision: a ready task is scheduled.
         **/
        void schedule()
        {
            executionQueue->insert(readyQueue->extract());
            (executionQueue->front())->setState(EXECUTING);
            publishEvent((executionQueue->front())->getTaskID(), SCHEDULE);
        }
        /**
         * Scheduling decision: a task with priority over the executing task
         * has become ready, and the scheduler is set to be preemptive, so the
         * ready task takes the CPU while the executing becomes ready.
         **/
        void preemption()
        {
            (executionQueue->front())->setState(READY);
            publishEvent
                ((executionQueue->front())->getTaskID(), PREEMPTION_ORIGIN);
            readyQueue->insert(executionQueue->extract());
            (readyQueue->front())->setState(EXECUTING);
            executionQueue->insert(readyQueue->extract());
            publishEvent
                ((executionQueue->front())->getTaskID(), PREEMPTION_DESTINATION);
            publishEvent
                ((executionQueue->front())->getTaskID(), SCHEDULE);
        }
    public:
        PriorityScheduler
            (
                bool preemptiveFlag,
                boost::shared_ptr<SystemQueuesManager> systemQueuesToSet,
                Timer* timerToSet,
                boost::shared_ptr<Activator> activatorToSet
            )
            :
            Scheduler
            (
                preemptiveFlag,
                systemQueuesToSet,
                timerToSet,
                activatorToSet
            )
        {
            readyQueue->setImplementation
                (readyQueueImplementationProvider.getImplementation());
            executionQueue->setImplementation
                (executionQueueImplementationProvider.getImplementation());
        }
        /**
         * The update method implementation is based on the concept of decision
         * tree. A decision tree is a tree where each node represents a
         * condition and each arch represents the actual value of the condition
         * node from which it exits, while its leaves represent the decision
         * that has to be taken when the condition represented by the AND
         * between all the condition values associated with the set of archs
         * composing a certain path is true. When an update occurs, the state of
         * the system queues is captured as a boolean vector which defines a
         * path from the root to a particular leave, and the related decision is
         *  taken. The implementation strategy is the following:
         * - for each set of leaves which represent the same decision:
         * -# write the general condition which individuates all those leaves in
         * the sum of products form, where each product is the AND between the
         * conditions which label each arch of a valid path and the overall sum
         * is the OR between all the products;
         * -# using a compound method (Quine McLuskey optimization and heuristic
         * optimization) reduce the sum of products to a short form, fast to
         * evaluate (notice that Quine McLuskey optimization is not always the
         * best choice in this sense);
         * -# use the obtained boolean expression as a condition for an if
         * statement whose then-block contains the related decision;
         **/
        void update(Subject* subject)
        {
            assert(StaticLog::log["general"] != NULL);
            std::ostream* log = StaticLog::log["general"];
            bool A = readyQueue->size() == 0;
            bool B = executionQueue->size() == 0;
            bool C =
                (B == false)
                &&
                (executionQueue->front())->getRemainingComputationTime() == 0;
            bool D =
                (B == false)
                &&
                ((executionQueue->front())->getPendingInstances() == 0);
            bool E = preemptionActivated;
            bool F =
                (A == false && B == false)
                &&
                comparator(readyQueue->front(), executionQueue->front());
            (*log) << "\tReady queue empty: "
                << ((A)? "true" : "false") << std::endl;
            (*log) << "\tExecution queue empty: "
                << ((B)? "true" : "false") << std::endl;
            (*log) << "\tExecuting Task terminated: "
                << ((C)? "true" : "false") << std::endl;
            (*log) << "\tPending instances of the executing Task: "
                << ((D)? "true" : "false") << std::endl;
            (*log) << "\tPreemption activated: "
                << ((E)? "true" : "false") << std::endl;
            (*log) << "\tIs there a ready Task with greater priority: "
                << ((F)? "true" : "false") << std::endl;
            if(((!B) && (!C) && ((!E) || (!F))) || (A && ((!C) || B)))
            {
                (*log) << "\tSCHEDULING DECISION: do nothing" << std::endl;
                publishEvent
                (
                    ((executionQueue->front()).get() == NULL)?
                    0 : (executionQueue->front())->getTaskID()
                    ,
                    SCHEDULE
                );
                return;
            }
            if((!B) && C & (!D) && ((!F) || A))
            {
                (*log)
                    << "\tSCHEDULING DECISION: re-schedule the currently executing Task"
                    << std::endl;
                reExecute();
                notify();
                return;
            }
            if(A && (!B) && C && D)
            {
                (*log) << "\tSCHEDULING DECISION: reactivate the currently executing Task"
                    << std::endl;
                reActivate();
                publishEvent(0, SCHEDULE);
                notify();
                return;
            }
            if((!A) && B)
            {
                (*log) << "\tSCHEDULING DECISION: schedule a ready task"
                    << std::endl;
                schedule();
                notify();
                return;
            }
            if((!A) && (!B) && C && D)
            {
                (*log) <<
                    "\tSCHEDULING DECISION: reactivate the currently executing Task and schedule a ready Task"
                    << std::endl;
                reActivate();
                schedule();
                notify();
                return;
            }
            if((!A) && (!B) && C && (!D) && F)
            {
                (*log) <<
                    "SCHEDULING DECISION: put the currently executing Task in the ready queue and schedule a ready task"
                    << std::endl;
                (executionQueue->front())->reset();
                preemption();
                notify();
                return;
            }
            if((!A) && (!B) && (!C) && E && F)
            {
                (*log) <<
                    "SCHEDULING DECISION: put the currently executing Task in the ready queue and schedule a ready task"
                    << std::endl;
                preemption();
                notify();
                return;
            }
            std::cout << "This should never be printed" << std::endl;
            assert(false);
            return;
        }
        void publishEvent(unsigned int taskID, SchedulingEventType typeOfEvent)
        {
            boost::shared_ptr< Event<unsigned int, unsigned int> > newEvent
            (
                (typeOfEvent == SCHEDULE)?
                    static_cast< Event<unsigned int, unsigned int>* >
                    (
                        new VisitableSchedulingEvent<SCHEDULE>
                        (taskID, timer->getCurrentTime())
                    )   
                :
                (typeOfEvent == PREEMPTION_ORIGIN)?
                    static_cast< Event<unsigned int, unsigned int>* >
                    (
                        new VisitableSchedulingEvent<PREEMPTION_ORIGIN>
                        (taskID, timer->getCurrentTime())
                    )
                :
                    static_cast< Event<unsigned int, unsigned int>* >
                    (
                        new VisitableSchedulingEvent<PREEMPTION_DESTINATION>
                        (taskID, timer->getCurrentTime())
                    )
            );
            insert(newEvent);
        }
};

#endif
