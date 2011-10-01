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
#define SINGLE_SLOT_IMPLEMENTATION_H

template <typename ElementType, typename Comparator>
class SingleSlotQueueImplementation : public QueueImplementation<ElementType>
{
    private:
        boost::shared_ptr<ElementType> dataStructure;
    public:
        /**
         * Insertion complexity: O(1) (Merge Sort).
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
        boost::shared_ptr<ElementType> front()
        {
            return dataStructure;
        }
        boost::shared_ptr<ElementType> back()
        {
            return dataStructure;
        }
        void print() //TODO remove this!
        {
            dataStructure->print();
        }
};

#endif
