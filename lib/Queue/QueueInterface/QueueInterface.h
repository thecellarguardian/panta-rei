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

/* To disable assertions:
 * #ifndef NDEBUG
 * #define NDEBUG
 * #endif
 */

#include <boost/shared_ptr.hpp>
#include <cassert>
#include "../QueueImplementation/QueueImplementation.h"
#include "../QueueImplementationProvider/QueueImplementationProvider.h"

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
         * The default constructor creates an interface without attaching any
         * implementation. This is useful in case of shared queues, where the
         * queue creator hasn't the needed knowledge to attach the proper
         * implementation. An example: a task activator needs to access a
         * "ready" queue (only to perform the insert operation), but it's the
         * scheduler that knows exactly what data structure should be used to
         * implement that queue (ordered list, hash map...) according to the
         * scheduling policy it implements. This leads to a strong procedural
         * constraint: lazy queue initialization is possible through the use
         * of the default constructor and the attachImplementation method, but
         * every queue client must be sure about the consistency of the queue
         * structure (the interface it refers must be provided with an
         * implementation).
         * @post An implementation must be provided before the queue is used.
         **/
        QueueInterface(){}
        /**
         * This constructor attaches the implementation to the queue interface.
         * @param queueImplementationToSet The implementation to be attached.
         * @pre queueImplementationToSet must refer a queue implementation.
         **/
        QueueInterface
            (
                boost::shared_ptr< QueueImplementation<T> >
                queueImplementationToSet
            )
            : queueImplementation(queueImplementationToSet)
            {
                assert(queueImplementationToSet.get() != NULL);
            }
        /**
         * The constructor takes a QueueImplementationProvider as an argument.
         * The implementation reference will be provided by this object, and
         * the QueueInterface will become the owner of the implementation.
         **/
        QueueInterface(QueueImplementationProvider<T>* implementationProvider)
            : queueImplementation(implementationProvider->getImplementation()){}
        void attachImplementation
            (
                boost::shared_ptr< QueueImplementation<T> >
                queueImplementationToSet
            )
        {
            assert(queueImplementationToSet.get() != NULL);
            queueImplementation = queueImplementationToSet;
        }
        virtual ~QueueInterface(){}
        /**
         * This method attaches a particular implementation to the queue
         * interface. If the interface was made using the default constructor,
         * this method has to be called before the interface using.
         * @param queueImplementationToSet The implementation to be set.
         **/
        void setImplementation
            (
                boost::shared_ptr< QueueImplementation<T> >
                queueImplementationToSet
            )
        {
            queueImplementation = queueImplementationToSet;
        }
        /**
         * The insert method is bound to the implementation method.
         * @param elementToInsert Element to be inserted.
         **/
        void insert(boost::shared_ptr<T> elementToInsert)
        {
            assert(queueImplementation.get() != NULL);
            if(elementToInsert.get() != NULL)
            {
                queueImplementation->insert(elementToInsert);
            }
        }
        /**
         * The extraction method is bound to the implementation method.
         * @return Extracted element.
         **/
        boost::shared_ptr<T> extract()
        {
            assert(queueImplementation.get() != NULL);
            return queueImplementation->extract();
        }
        boost::shared_ptr<T> front()
        {
            assert(queueImplementation.get() != NULL);
            return queueImplementation->front();
        }
        boost::shared_ptr<T> back()
        {
            assert(queueImplementation.get() != NULL);
            return queueImplementation->back();
        }
        void print()
        {
            queueImplementation->print();
        }
};

#endif
