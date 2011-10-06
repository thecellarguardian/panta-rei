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
#include "../Scheduler.h"
#include "../../../../lib/Queue/QueueImplementationProvider/QueueImplementationProvider.h"
#include "../../../../lib/Queue/Implementations/OrderedQueueImplementation/OrderedQueueImplementation.h"
#include "../../../../lib/Queue/Implementations/SingleSlotQueueImplementation/SingleSlotQueueImplementation.h"
#include "../../Activator/Activator.h"
#include "../../Task/Task.h"

#ifndef DEADLINE_MONOTONIC_H
#define DEADLINE_MONOTONIC_H

class RelativeDeadlineComparator
{
    public:
        bool operator()(boost::shared_ptr<Task>& a, boost::shared_ptr<Task>& b);
};

class DeadlineMonotonic : public Scheduler
{
    private:
        QueueImplementationProvider
            <OrderedQueueImplementation< Task, RelativeDeadlineComparator> >
            readyQueueImplementationProvider;
        QueueImplementationProvider< SingleSlotQueueImplementation<Task> >
            executionQueueImplementationProvider;
        boost::shared_ptr<Activator> activator;
    public:
        DeadlineMonotonic
            (
                bool preemptiveFlag,
                boost::shared_ptr<SystemQueuesManager> systemQueuesToSet,
                Timer* timerToSet,
                boost::shared_ptr<Activator> activatorToSet
            );
        void update();
};

#endif
