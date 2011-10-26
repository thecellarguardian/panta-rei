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
#include "../../../lib/Queue/Implementations/OrderedQueueImplementation/OrderedQueueImplementation.h"

#ifndef ACTIVATOR_H
#define ACTIVATOR_H

class ArrivalTimeComparator
{
    public:
        bool operator()(boost::shared_ptr<Task>& a, boost::shared_ptr<Task>& b);
};

/**
 * @class Activator
 * @brief A task manager for task activation.
 * An Activator is a Timer observer. It has references to the activation and the
 * ready queue. When an activator is updated, it checks if there are tasks to be
 * activated, that is, it has to extract those tasks from the activation queue
 * and put them in the ready queue. The complexity of this task is O(nlog(n)),
 * since the extraction from the activation queue (ordered by arrival time) is
 * O(1) and the insertion in the ready queue (also an ordered queue) is, in the
 * worst case, O(nlog(n)) (Merge Sort).
 **/
class Activator : public Observer
{
    private:
        QueueImplementationProvider
            < OrderedQueueImplementation<Task, ArrivalTimeComparator> >
            queueImplementationProvider;
        /**<
         * The activator owns the activation queue, so it's its duty to attach a
         * proper implementation to the QueueInterface object returned by the
         * SystemQueuesManager naming service. The best solution is to have the
         * queue ordered by arrival Time, so that the extraction is very
         * efficient (O(1)) and the insertion is not unefficient (O(nlog(n))).
         **/
        boost::shared_ptr<SystemQueuesManager> systemQueues;
        /**< Shared pointer to the system wide queue naming system.**/
        boost::shared_ptr< QueueInterface<Task> > activationQueue;
        /**< Shared pointer to the activation queue.**/
        boost::shared_ptr< QueueInterface<Task> > readyQueue;
        /**< Shared pointer to the ready queue.**/
        Timer* timer;
        /**<
         * Pointer to the Timer. A normal pointer is used, due to avoid
         * the shared pointer circular reference problem.
         **/
    public:
        Activator
            (
                boost::shared_ptr<SystemQueuesManager> systemQueuesToSet,
                Timer* timerToSet
            );
        virtual ~Activator();
        /**
         * When the activator is updated, it moves the ready to be activated
         * tasks into the ready queue.
         **/
        void update(Subject* subject);
        /**
         * This method registers a task for activation, that is, a shared
         * pointer to it is placed into the activation queue.
         **/
        void registerForActivation(boost::shared_ptr<Task> taskToRegister);
        void print();
};

#endif
