/**
 * @file EventSource.h
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

#include "../../Queue/QueueInterface/QueueInterface.h"
#include "../../Queue/QueueImplementation/QueueImplementation.h"
#include "../../DesignPatterns/Observer/Subject.h"
#include "../Event/Event.h"

#ifndef EVENT_SOURCE_H
#define EVENT_SOURCE_H

 /**
 * @class EventSource
 * @brief A generic source of events.
 * This class models a generic source of events.
 * It is a QueueInterface and a Subject, and it's template parametric in a
 * ParticularQueueImplementation, so that every event can be stored in a proper
 * data structure. An event source can store events in its queue,
 * and, when the right time arrives, a call to the inherited notify() method
 * will let every Observer know that events have been produced, so that they can
 * get them through the getEventList() method.
 * @tparam QueueImplementor A particular QueueImplementation class.
 * @see Subject, QueueInterface, QueueImplementation, Event
 **/
//TODO: add a withMemory flag to give the possibility to store all past events
//even after a notify call. Notice that this change could make the interface
//grow with temporal query wrappers and stuff...
template <typename EventType> class EventSource
    :
    public QueueInterface<EventType>, public Subject
{
    public:
        EventSource(){}
        virtual void notify()
        {
            std::list<Observer*>::iterator i = attachedObservers.begin();
            for(; i != attachedObservers.end(); i++)
            {
                (*i)->update(this);
            }
            this->resetQueue();
        }
        /**
         * This method returns a copy of the event queue. It is intended to be
         * used by the notified objects.
         **/
        boost::shared_ptr< QueueImplementation<EventType> > getEventList()
        {
            boost::shared_ptr< QueueImplementation<EventType> >
                eventQueue(this->queueImplementation->clone());
            return eventQueue;
        }
};

#endif
