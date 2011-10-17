/**
 * @file SystemQueuesManager.h
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
#include <map>
#include "../../../lib/Queue/QueueInterface/QueueInterface.h"
#include "../Task/Task.h"

#ifndef SYSTEM_QUEUES_MANAGER_H
#define SYSTEM_QUEUES_MANAGER_H

/**
 * @class SystemQueuesManager
 * @brief Naming service for system queues.
 * This class offers a simple yet effective way to refer system queues: a queue
 * can be simply obtained by name. If the name provided names an existing queue,
 * a shared pointer to its QueueInterface is returned. If the name does not name
 * an existing queue, a new QueueInterface is created and a shared pointer to it
 * is returned. Notice that this newly created QueueInterface has no
 * implementation attached, so you have to be sure that, when the QueueInterface
 * is used, an implementation for it exists.
 **/
class SystemQueuesManager
{
    private:
        std::map< std::string, boost::shared_ptr< QueueInterface<Task> > >
        queueRegistry;
    public:
        virtual ~SystemQueuesManager();
        /**
         * Returns the QueueInterface object related to the specified name.
         * If the specified name does not name any existing queue, a new
         * QueueInterface is created; its client has to be sure that an
         * implementation has been attached to it before using it.
         * @post The returned QueueInterface could be a newly created object
         * (this happens if the specified name does not name an existing queue),
         * so the queue client has to be sure that the QueueInterface has been
         * initialized with a proper implementation.
         **/
        boost::shared_ptr< QueueInterface<Task> >& operator[](std::string key);
};

#endif
