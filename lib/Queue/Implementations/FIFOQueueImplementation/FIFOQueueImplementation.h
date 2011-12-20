/**
 * @file FIFOQueueImplementation.h
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

 #ifndef FIFO_QUEUE_IMPLEMENTATION_H
 #define FIFO_QUEUE_IMPLEMENTATION_H

/**
 * @class FIFOQueueImplementation
 * @brief An FIFO queue implementation.
 * A simple FIFO queue implementation. This implementation is a simple
 * std::list<T> wrapper. 
 * @tparam ElementType The type of the elements.
 **/
template <typename ElementType>
class FIFOQueueImplementation : public QueueImplementation<ElementType>
{
    private:
        std::list< boost::shared_ptr<ElementType> > dataStructure;
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
            return new FIFOQueueImplementation<ElementType>(*this);
        }
        /**
         * Insertion complexity: O(n) or O(1) depending on std::list<T>
         * implementation..
         **/
        virtual void insert(boost::shared_ptr<ElementType> elementToInsert)
        {
            dataStructure.push_back(elementToInsert);
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
};

#endif
