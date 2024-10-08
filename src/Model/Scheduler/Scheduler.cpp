/**
 * @file Scheduler.cpp
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

#include "Scheduler.h"
#include "../../../lib/Queue/Implementations/FIFOQueueImplementation/FIFOQueueImplementation.h"

Scheduler::Scheduler
    (
        bool preemptiveFlag,
        boost::shared_ptr<SystemQueuesManager> systemQueuesToSet,
        Timer* timerToSet,
        boost::shared_ptr<Activator> activatorToSet
    )
    :
    preemptionActivated(preemptiveFlag),
    systemQueues(systemQueuesToSet),
    timer(timerToSet),
    activator(activatorToSet)
{
    if(timer != NULL)
    {
        timer->attach(this);
    }
    readyQueue = (*systemQueues)["ready"];
    executionQueue = (*systemQueues)["execution"];
    /*
     * Notice that the queue implementation initialization has to be done in
     * the derived classes, since only the particular scheduler knows which is
     * the queue implementation it needs.
     */
     //TODO
    //<reduntant code to refactor>
    boost::shared_ptr
        <
        FIFOQueueImplementation
            <
            Event
                <
                unsigned int,
                unsigned int
                >
            >
        >
        implementation
        (
            new FIFOQueueImplementation
            <
            Event
                <
                unsigned int,
                unsigned int
                >
            >
        );
    setImplementation(implementation);
    //</reduntant code to refactor>
}

Scheduler::~Scheduler()
{
    if(timer != NULL)
    {
        timer->detach(this);
    }
}
