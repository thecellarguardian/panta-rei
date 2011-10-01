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
#include "../../../../lib/Queue/Implementations/OrderedQueueImplementation.h"
#include "../../../../lib/Queue/Implementations/SingleSlotQueueImplementation.h"
#include "../../Task/Task.h"

#ifndef DEADLINE_MONOTONIC_H
#define DEADLINE_MONOTONIC_H

class RelativeDeadlineComparator
{
    public:
        bool operator()(boost::shared_ptr<Task>& a, boost::shared_ptr<Task>& b)
        {
            return (a->getRelativeDeadline() < b->getRelativeDeadline());
        }
};

class DeadlineMonotonic : public Scheduler
{
    private:
        QueueImplementationProvider
            <OrderedQueueImplementation< Task, RelativeDeadlineComparator> >
            readyQueueImplementationProvider;
        QueueImplementationProvider< SingleSlotQueueImplementation<Task> >
            executionQueueImplementationProvider;
    public:
        DeadlineMonotonic();
        void update();
};

#endif
