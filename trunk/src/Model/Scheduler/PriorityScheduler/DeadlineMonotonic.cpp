/**
 * @file DeadlineMonotonic.cpp
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

#include "DeadlineMonotonic.h"
#include "../../Task/PeriodicTask/PeriodicTask.h"

bool RelativeDeadlineComparator::
    operator()(boost::shared_ptr<Task>& a, boost::shared_ptr<Task>& b)
{
    return (a->getRelativeDeadline() < b->getRelativeDeadline());
}

DeadlineMonotonic::DeadlineMonotonic
    (
        bool preemptiveFlag,
        boost::shared_ptr<SystemQueuesManager> systemQueuesToSet,
        Timer* timerToSet,
        boost::shared_ptr<Activator> activatorToSet
    )
    :
    Scheduler(preemptiveFlag, systemQueuesToSet, timerToSet),
    activator(activatorToSet)
{
    readyQueue->setImplementation
        (readyQueueImplementationProvider.getImplementation());
    executionQueue->setImplementation
        (executionQueueImplementationProvider.getImplementation());
}

void DeadlineMonotonic::update()
{
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
        (
            (readyQueue->front())->getRelativeDeadline()
            <
            (executionQueue->front())->getRelativeDeadline()
        );
        std::cout << "readyQueue empty: " << ((A)? "true" : "false") << std::endl;
        std::cout << "executionQueue empty: "
            << ((B)? "true" : "false") << std::endl;
        std::cout << "executing Task terminated: "
            << ((C)? "true" : "false") << std::endl;
        std::cout << "Are there pending instances of the executing task: "
            << ((D)? "false" : "true") << std::endl;
        std::cout << "preemption: " << ((E)? "true" : "false") << std::endl;
        std::cout << "Is there a ready Task with greater priority: "
            << ((F)? "true" : "false") << std::endl;
    if(((!B) && (!C) && ((!E) || (!F))) || (A && ((!C) || B)))
    {
        std::cout << "SCHEDULING DECISION: return" << std::endl;
        return;
    }
    if((!B) && C & (!D) && ((!F) || A))
    {
        std::cout << "SCHEDULING DECISION: reset execution and re-schedule it"
            << std::endl;
        (executionQueue->front())->reset();
        (executionQueue->front())->setState(EXECUTING);
        return;
    }
    if(A && (!B) && C && D)
    {
        std::cout << "SCHEDULING DECISION: reactivate execution" << std::endl;
        (executionQueue->front())->reset();
        activator->registerForActivation(executionQueue->extract());
        return;
    }
    if((!A) && B)
    {
        std::cout << "SCHEDULING DECISION: schedule a ready task" << std::endl;
        (readyQueue->front())->setState(EXECUTING);
        executionQueue->insert(readyQueue->extract());
        return;
    }
    if((!A) && (!B) && C && D)
    {
        std::cout <<
            "SCHEDULING DECISION: reactivate execution, schedule a ready task"
            << std::endl;
        (executionQueue->front())->reset();
        activator->registerForActivation(executionQueue->extract());
        executionQueue->insert(readyQueue->extract());
        (executionQueue->front())->setState(EXECUTING);
        return;
    }
    if((!A) && (!B) && C && (!D) && F)
    {
        std::cout <<
            "SCHEDULING DECISION: reset execution and put it in ready, \
            schedule a ready task"
            << std::endl;
        (executionQueue->front())->reset();
        (executionQueue->front())->setState(READY);
        readyQueue->insert(executionQueue->extract());
        executionQueue->insert(readyQueue->extract());
        (executionQueue->front())->setState(EXECUTING);
        return;
    }
    if((!A) && (!B) && (!C) && E && F)
    {
        std::cout <<
            "SCHEDULING DECISION: put execution in ready and schedule a ready \
            task"
            << std::endl;
        (executionQueue->front())->setState(READY);
        readyQueue->insert(executionQueue->extract());
        (readyQueue->front())->setState(EXECUTING);
        executionQueue->insert(readyQueue->extract());
        return;
    }
    std::cout << "This should never be printed" << std::endl;
    assert(false);
    return;
}
