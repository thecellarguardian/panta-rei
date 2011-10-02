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
    activator(activatoToSet)
{
    readyQueue->setImplementation
        (readyQueueImplementationProvider.getImplementation());
    executionQueue->setImplementation
        (executionQueueImplementationProvider.getImplementation());
}

void DeadlineMonotonic::update()
{
    if
        (
            (
                (
                    readyQueue->first()->getRelativeDeadline() <
                    executionQueue->first()->getRelativeDeadline()
                )
                &&
                (
                    preemptionActivated
                )
            )
            ||
            (executionQueue->getRemainingComputationTime() == 0)
        )
    {
        boost::shared_ptr<Task> executingTask(executionQueue->extract());
        boost::shared_ptr<Task> nextExecutingTask(readyQueue->extract());
        executionQueue->insert(nextExecutingTask);
        if
            (
                (
                    executingTask.get() != NULL
                    /*
                     * We're taking advantage of the AND short-circuit
                     * evaluation.
                     */
                )
                &&
                (
                    executingTask->getRemainingComputationTime() == 0
                )
            )
        {
            executingTask->reset();
            activator->registerForActivation(executingTask);
        }
        else
        {
            readyQueue.insert(executingTask);
        }
    }
}
