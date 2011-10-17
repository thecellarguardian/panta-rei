/**
 * @file SingleSlotQueueImplementation.h
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
#include "../../QueueImplementation/QueueImplementation.h"

#ifndef SINGLE_SLOT_QUEUE_IMPLEMENTATION_H
#define SINGLE_SLOT_QUEUE_IMPLEMENTATION_H

/**
 * @class SingleSlotQueueImplementation
 * @brief A single slot queue implementation.
 * This is a bounded queue implementation, it refers a queue that can maintain
 * no more than one element.
 **/
template <typename ElementType>
class SingleSlotQueueImplementation : public QueueImplementation<ElementType>
{
    private:
        boost::shared_ptr<ElementType> dataStructure;
    public:
        /**
         * Insertion complexity: O(1). The insertion is always possible, but if
         * the queue is not empty, the previous element is lost.
         **/
        void insert(boost::shared_ptr<ElementType> elementToInsert)
        {
            dataStructure = elementToInsert;
        }
        /**
         * Extraction complexity: O(1).
         **/
        virtual boost::shared_ptr<ElementType> extract()
        {
            boost::shared_ptr<ElementType> pointerToReturn = dataStructure;
            dataStructure.reset();
            return pointerToReturn;
        }
        /**
         * This method returns a shared pointer to the maintained element.
         **/
        boost::shared_ptr<ElementType> front()
        {
            return dataStructure;
        }
        /**
         * This method returns a shared pointer to the maintained element.
         **/
        boost::shared_ptr<ElementType> back()
        {
            return front();
        }
        /**
         * This method returns the size of the queue. Notice that this method
         * could be intended as a bool isFull method.
         **/
        unsigned int size()
        {
            return (dataStructure.get() == NULL)? 0 : 1;
        }
        void print() //TODO remove this!
        {
            dataStructure->print();
        }
};

#endif
