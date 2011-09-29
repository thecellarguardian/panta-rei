/**
 * @file QueueImplementation.h
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

#ifndef QUEUE_IMPLEMENTATION_H
#define QUEUE_IMPLEMENTATION_H

/**
 * @class QueueImplementation
 * @brief Interface of a queue implementation class.
 * This class provides the interface for a queue implementation class. By mean
 * of derivation, a particular class can define particular data structures to be
 * used and particular policies for the insert and extract operations.
 **/
template <typename T> class QueueImplementation
{
    public:
        virtual ~QueueImplementation(){}
        virtual void insert(boost::shared_ptr<T> elementToInsert) = 0;
        virtual boost::shared_ptr<T> extract() = 0;
        virtual boost::shared_ptr<T> front() = 0;
        virtual boost::shared_ptr<T> back() = 0;
        virtual void print() = 0;
};

#endif
