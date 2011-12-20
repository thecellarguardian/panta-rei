/**
 * @file History.h
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


#include "../../../lib/DesignPatterns/Observer/Observer.h"
#include "../../../lib/DesignPatterns/Visitor/VisitorAcceptor.h"
#include "../../../lib/Queue/Implementations/FIFOQueueImplementation/FIFOQueueImplementation.h"
#include <cassert>
#include <iostream>

#ifndef HISTORY_H
#define HISTORY_H

/**
 * @class History
 * @brief History.
 * This class is a multi-subject Observer, it registers to several
 * EventSource<EventType> and, being a Queue, it stores the produced events.
 * History is also a VisitorAcceptor, so that the stored data can be read and
 * elaborated to produce several aggregate information.
 **/
template <typename EventType> class History
    :
    public QueueInterface<EventType>,
    public Observer,
    public VisitorAcceptor
{
    public:
        /**
         * History is a QueueInterface, which knows itself which implementation
         * to use: since it stores temporal information, a FIFOQueueImplementation
         * is proper.
         **/
        History()
        {
            boost::shared_ptr< FIFOQueueImplementation<EventType> >
                implementation(new FIFOQueueImplementation<EventType>);
            setImplementation(implementation);
        }
        /**
         * An History object can register to several EventSource<EventType>,
         * which update it when a new Event list is available. History gets the
         * list and stores each Event, checking that it is also a
         * VisitorAcceptor.
         **/
        void update(Subject* subject)
        {
            EventSource<EventType>* eventSource =
                dynamic_cast< EventSource< EventType >* >(subject);
            assert(eventSource != NULL);
            boost::shared_ptr< QueueImplementation<EventType> >
                eventList(eventSource->getEventList());
            while(eventList->size() > 0)
            {
                boost::shared_ptr<EventType> eventToCopy(eventList->extract());
                assert
                    ((dynamic_cast<VisitorAcceptor*>(eventToCopy.get())) != NULL);
                insert(eventToCopy);
            }
        }
        /**
         * For each stored Event, History lets the passed Visitor visit it.
         **/
        void accept(Visitor* visitor) //TODO IMPLEMENT ITERATORS FOR THE QUEUE LIB!
        {
            for(unsigned int i = 0; i < this->size(); i++)
            {
                boost::shared_ptr<VisitorAcceptor> acceptor =
                    boost::dynamic_pointer_cast<VisitorAcceptor>(this->front());
                acceptor->accept(visitor);
                this->insert(this->extract());
                // IT WORKS BUT IT'S AWFUL
            }
        }
        /**
         * This metod lets History register to several EventSource<EventType>.
         **/
        void registerToEventSource(EventSource<EventType>* eventSource)
        {
            eventSource->attach(this);
        }
        /**
         * Reset method.
         **/
        void clear()
        {
            boost::shared_ptr< FIFOQueueImplementation<EventType> >
                implementation(new FIFOQueueImplementation<EventType>);
            setImplementation(implementation);
        }
};

#endif
