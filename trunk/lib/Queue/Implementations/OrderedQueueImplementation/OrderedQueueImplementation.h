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

 #ifndef ORDERED_QUEUE_IMPLEMENTATION_H
 #define ORDERED_QUEUE_IMPLEMENTATION_H
 

template <typename ElementType, typename Comparator> class OrderedQueueImplementation
{
    private:
        std::list< shared_ptr<T> > dataStructure;
    public:
        void insert(boost::shared_ptr<T> elementToInsert)
        {
            Comparator comparationOperator;
            dataStructure.push_back(elementToInsert);
            dataStructure.sort(comparationOperator);
        }
        virtual boost::shared_ptr<T> extract()
        {
            if(dataStructure.size() > 0)
            {
                return dataStructure.pop_front();
            }
            boost::shared_ptr<T> nullPointer;
            return nullPointer;
        }
};

#endif
