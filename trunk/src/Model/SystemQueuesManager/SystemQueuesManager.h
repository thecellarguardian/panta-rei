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

class SystemQueuesManager
{
    private:
        std::map< std::string, boost::shared_ptr< QueueInterface<Task> > >
        queueRegistry;
    public:
        boost::shared_ptr< QueueInterface<Task> >& operator[](std::string key);
};

#endif
