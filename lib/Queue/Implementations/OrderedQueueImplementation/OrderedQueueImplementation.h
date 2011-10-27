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

/**
 * @class OrderedQueueImplementation
 * @brief An ordered queue implementation.
 * This queue implementation maintains an ordered queue of ElementType objects.
 * The objects are ordered using the Comparator sorting relation. A Comparator
 * is a functor which takes two arguments and returns true if the first is minor
 * than the second. This particular implementation adds a level of indirection:
 * the actual elements stored in the queue are shared pointers to the meaningful
 * elements to manipulate. Notice that the use of shared pointers implies that
 * the managed objects could be shared with other entities.
 * @tparam ElementType The type of the elements.
 * @tparam Comparator The ordering law.
 **/
template <typename ElementType, typename Comparator>
class OrderedQueueImplementation : public QueueImplementation<ElementType>
{
    private:
        std::list< boost::shared_ptr<ElementType> > dataStructure;
        Comparator comparationOperator;
    public:
        /**
         * The default copy constructor is suitable for this copy. It will
         * call the std::list< boost::shared_ptr<ElementType> > copy
         * constructor, which makes a simple copy element by element, and
         * that's not a problem, since boost::shared_ptr<ElementType> is
         * copy safe (a copy of a shared pointer is a valid shared pointer
         * which points the same object). Remember, the cloned queue will
         * refer the same objects referred by the original one.
         **/
        virtual QueueImplementation<ElementType>* clone()
        {
            return
                new OrderedQueueImplementation<ElementType, Comparator>(*this);
        }
        /**
         * Insertion complexity: O(n*log(n)) (Merge Sort).
         **/
        virtual void insert(boost::shared_ptr<ElementType> elementToInsert)
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
        /**
         * This method returns a shared pointer to the first element. Remember,
         * boost::shared_ptr is copy safe.
         **/
        boost::shared_ptr<ElementType> front()
        {
            boost::shared_ptr<ElementType> nullPointer;
            return (dataStructure.size() > 0)?
                dataStructure.front() : nullPointer;
        }
        /**
         * This method returns a shared pointer to the last element. Remember,
         * boost::shared_ptr is copy safe.
         **/
        boost::shared_ptr<ElementType> back()
        {
            boost::shared_ptr<ElementType> nullPointer;
            return (dataStructure.size() > 0)?
                dataStructure.back() : nullPointer;
        }
        /**
         * This method returns the size of the queue.
         **/
        unsigned int size()
        {
            return dataStructure.size();
        }
        void print() //TODO remove this!
        {
            typename std::list< boost::shared_ptr<ElementType> >::iterator i =
            dataStructure.begin();
            for(; i != dataStructure.end(); i++)
            {
                (*i)->print();
            }
        }
};

#endif
