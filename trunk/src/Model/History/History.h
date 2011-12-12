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

template <typename EventType> class History
    :
    public QueueInterface<EventType>,
    public Observer,
    public VisitorAcceptor
{
    public:
        History()
        {
            boost::shared_ptr< FIFOQueueImplementation<EventType> >
                implementation(new FIFOQueueImplementation<EventType>);
            setImplementation(implementation);
        }
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
                std::cout << "history >> NEW EVENT: subject:"
                    << eventToCopy->getSubject() << " instant: "
                    << eventToCopy->getInstant() << std::endl;
                insert(eventToCopy);
            }
        }
        void accept(Visitor* visitor) //TODO IMPLEMENT ITERATORS FOR THE QUEUE LIB!
        {
            std::cout
                << "Accepting visitor, total history size: "
                << this->size()
                << std::endl;
            for(unsigned int i = 0; i < this->size(); i++)
            {
                boost::shared_ptr<VisitorAcceptor> acceptor =
                    boost::dynamic_pointer_cast<VisitorAcceptor>(this->front());
                acceptor->accept(visitor);
                this->insert(this->extract());
                // IT WORKS BUT IT'S AWFUL
            }
        }
        void registerToEventSource(EventSource<EventType>* eventSource)
        {
            std::cout << "Registering to event source: " << (void*)eventSource << std::endl;
            eventSource->attach(this);
        }
        void clear()
        {
            boost::shared_ptr< FIFOQueueImplementation<EventType> >
                implementation(new FIFOQueueImplementation<EventType>);
            setImplementation(implementation);
        }
};

#endif
