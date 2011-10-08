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
    activator(activatorToSet)
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
            (readyQueue->size() == 0)
            &&
            (
                executionQueue->size() == 0
                ||
                (executionQueue->front())->getRemainingComputationTime() > 0
            )
        )
        ||
        (
            (readyQueue->size() > 0)
            &&
            (executionQueue->size() > 0)
            &&
            ((executionQueue->front())->getRemainingComputationTime() > 0)
            &&
            (
                (!preemptionActivated)
                ||
                (
                    (readyQueue->front())->getRelativeDeadline() >=
                    (executionQueue->front())->getRelativeDeadline()
                )
            )
        )
    )
    {
        return;
    }
    if
    (
        (readyQueue->size() > 0)
        &&
        (executionQueue->size() > 0)
        &&
        ((executionQueue->front())->getRemainingComputationTime() == 0)
        &&
        (
            ((executionQueue->front())->getRemainingPeriod() > 0)
            ||
            (!preemptionActivated)
        )
    )
    {
        (executionQueue->first())->reset();
        activator->registerForActivation(executionQueue->first());
        executionQueue->extract();
        executionQueue->insert(readyQueue->extract());
    }
    //std::cout << "Scheduler is active" << std::endl;
    //if(readyQueue->size() == 0) return;
    //std::cout << "The ready queue is not empty" << std::endl;
    //if
        //(
            //(
                //executionQueue->size() == 0
                ///*
                 //* We're taking advantage of the OR short-circuit evaluation.
                 //*/
            //)
            //||
            //(
                //(
                    //(readyQueue->front())->getRelativeDeadline() <
                    //(executionQueue->front())->getRelativeDeadline()
                //)
                //&&
                //(
                    //preemptionActivated
                //)
            //)
            //||
            //(executionQueue->front()->getRemainingComputationTime() == 0)
        //)
    //{
        //std::cout << "A task is being scheduled" << std::endl;
        //boost::shared_ptr<Task> executingTask(executionQueue->extract());
        //boost::shared_ptr<Task> nextExecutingTask(readyQueue->extract());
        //nextExecutingTask->setState(EXECUTING);
        //executionQueue->insert(nextExecutingTask);
        //if(executingTask.get() == NULL) return;
        //if(executingTask->getRemainingComputationTime() == 0)
        //{
            ////What happens if the exiting task must be immediately re-scheduled?
            //executingTask->reset();
            //activator->registerForActivation(executingTask);
        //}
        //else
        //{
            //executingTask->setState(READY);
            //readyQueue->insert(executingTask);
        //}
    //}
}
