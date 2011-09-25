/**
 * @file OrderedQueueImplementation.h
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
 #include <list>
 #include "../../QueueImplementation/QueueImplementation.h"

 #ifndef ORDERED_QUEUE_IMPLEMENTATION_H
 #define ORDERED_QUEUE_IMPLEMENTATION_H

template <typename ElementType, typename Comparator>
class OrderedQueueImplementation : public QueueImplementation<ElementType>
{
    private:
        std::list< boost::shared_ptr<ElementType> > dataStructure;
        Comparator comparationOperator;
    public:
        /**
         * Insertion complexity: O(n*log(n)) (Merge Sort).
         **/
        void insert(boost::shared_ptr<ElementType> elementToInsert)
        {
            dataStructure.push_back(elementToInsert);
            dataStructure.sort(comparationOperator);
        }
        /**
         * Extraction complexity: O(1).
         **/
        virtual boost::shared_ptr<ElementType> extract()
        {
            if(dataStructure.size() > 0)
            {
                boost::shared_ptr<ElementType> pointerToReturn =
                    dataStructure.front();
                dataStructure.pop_front();
                return pointerToReturn;
            }
            boost::shared_ptr<ElementType> nullPointer;
            return nullPointer;
        }
};

#endif
