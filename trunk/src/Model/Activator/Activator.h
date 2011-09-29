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

#include "../../../lib/DesignPatterns/Observer/Observer.h"
#include
"../../../lib/Queue/QueueImplementationProvider/QueueImplementationProvider.h"

#ifndef ACTIVATOR_H
#define ACTIVATOR_H

class ArrivalTimeComparator
{
    public:
        bool operator()(boost::shared_ptr<Task>& a, boost::shared_ptr<Task>& b)
        {
            return
                (
                    a->getCurrentInstanceArrivalTime() <
                    b->getCurrentInstanceArrivalTime()
                );
        }
};

class Activator : public Observer, public QueueImplementationProvider
{
    private:
        ArrivalTimeComparator taskComparator;
        boost::shared_ptr< QueueImplementation<Task> > activationQueue;
    public:
        Activator();
        void update();
        boost::shared_ptr< QueueImplementation<Task> > getImplementation();
};

#endif
