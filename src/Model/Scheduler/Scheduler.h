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
#include "../../../lib/Queue/Providers/OrderedQueueImplementationProvider/OrderedQueueImplementationProvider.h"
#include "../../../lib/Queue/QueueInterface/QueueInterface.h"
#include "../SystemQueuesManager/SystemQueuesManager.h"
#include "../Task/Task.h"
#include "../Timer/Timer.h"
#include <boost/shared_ptr.hpp>

#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler : public Observer
{
    private:
        bool preemptionActivated;
        boost::shared_ptr<SystemQueuesManager> systemQueues;
        boost::shared_ptr< QueueInterface<Task> > readyQueue;
        boost::shared_ptr< QueueInterface<Task> > executionQueue;
        Timer* timer;
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
