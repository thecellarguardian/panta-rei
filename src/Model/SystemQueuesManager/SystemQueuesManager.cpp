/**
 * @file SystemQueuesManager.cpp
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

#include "SystemQueuesManager.h"
#include <iostream>

SystemQueuesManager::~SystemQueuesManager(){}

boost::shared_ptr< QueueInterface<Task> >&
SystemQueuesManager::operator[](std::string key)
{
    if(queueRegistry.find(key) == queueRegistry.end())
    {
        std::cout << "The " << key << " queue is being created" << std::endl;
        boost::shared_ptr< QueueInterface<Task> > pointerToInsert
        (new QueueInterface<Task>());
        std::pair
            <
                std::string, boost::shared_ptr
                    <
                        QueueInterface<Task>
                    >
            > pairToInsert(key, pointerToInsert);
        queueRegistry.insert(pairToInsert);
    }
    return queueRegistry[key];
}