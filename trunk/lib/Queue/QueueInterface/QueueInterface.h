/**
 * @file SystemQueueInterface.h
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

#ifndef QUEUE_INTERFACE_H
#define QUEUE_INTERFACE_H

/**
 * @class QueueInterface
 * @brief Interface to a generic queue.
 * This class, toghether with QueueImplementation, implements a generic queue.
 * A QueueInterface object exposes the queue interface and holds a reference to
 * a QueueImplementation object, which implements the data structure and access
 * policy for the particular queue.
 **/
template<typename T> class QueueInterface
{
    private:
        boost::shared_ptr< QueueImplementation<T> > queueImplementation;
    public:
        /**
         * The constructor takes a QueueImplementationProvider as an argument.
         * The implementation reference will be provided by this object, and
         * the QueueInterface will become the owner of the implementation.
         **/
        QueueInterface(QueueImplementationProvider* implementationProvider)
            : queueImplementation(implementationProvider->getImplementation())
            {}
        /**
         * The insert method is bound to the implementation method.
         * @param elementToInsert Element to be inserted.
         **/
        void insert(boost::shared_ptr<T> elementToInsert)
        {
            queueImplementation->insert(elementToInsert);
        }
        /**
         * The extraction method is bound to the implementation method.
         * @return Extracted element.
         **/
        boost::shared_ptr<T> extract()
        {
            return queueImplementation->extract();
        }
};

#endif
