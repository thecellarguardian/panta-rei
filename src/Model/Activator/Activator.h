/**
 * @file Activator.h
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

#include "../Timer/Timer.h"
#include "../Task/Task.h"
#include "../SystemQueuesManager/SystemQueuesManager.h"
#include "../../../lib/DesignPatterns/Observer/Observer.h"
#include "../../../lib/Queue/QueueImplementationProvider/QueueImplementationProvider.h"
#include "../../../lib/Queue/Implementations/OrderedQueueImplementation.h"

#ifndef ACTIVATOR_H
#define ACTIVATOR_H

class ArrivalTimeComparator
{
    public:
        bool operator()(boost::shared_ptr<Task>& a, boost::shared_ptr<Task>& b);
};

class Activator : public Observer
{
    private:
        QueueImplementationProvider
            < OrderedQueueImplementation<Task, ArrivalTimeComparator> >
            queueImplementationProvider;
        boost::shared_ptr<SystemQueuesManager> systemQueues;
        boost::shared_ptr< QueueInterface<Task> > activationQueue;
        boost::shared_ptr< QueueInterface<Task> > readyQueue;
        Timer* timer;
    public:
        Activator
            (
                boost::shared_ptr<SystemQueuesManager> systemQueuesToSet,
                Timer* timerToSet
            );
        virtual ~Activator();
        void update();
        void registerForActivation(boost::shared_ptr<Task> taskToRegister);
        void print();
};

#endif
