/**
 * @file VisitableSchedulingEvent.h
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

#include "../../../lib/DesignPatterns/Visitor/VisitorAcceptor.h"
#include "../../../lib/DesignPatterns/Visitor/Visitor.h"
#include "../../../lib/EventManagement/Event/Event.h"
#include "SchedulingEventType.h"
#include "SchedulingEventVisitor.h"
#include <iostream>

#ifndef VISITABLE_SCHEDULING_EVENT_H
#define VISITABLE_SCHEDULING_EVENT_H

/**
 * @class VisitableSchedulingEvent
 * @brief Generic visitable scheduling event.
 * An Event, as said in the Event class description, is composed by 3
 * information: a subject, an instant (happening) and the particular action
 * performed. This last information can be deduced looking at the particular
 * event type. What's the point of the enumerate template parametrization? It's
 * only a silly trick to avoid the re-writing of the same class: every
 * VisitableSchedulingEvent has an accept method, and this method is, formally,
 * always the same (it calls visit(this) on the visitor). The actual member
 * called on visitor, however, changes according to the caller's type (visit is
 * an overloaded method), so, if accept were a superclass method, the called
 * visit method would be everytime the same (since the type of the this pointer
 * passed is always a pointer to the superclass, notice that in this condition
 * the actual event type is unknown, so downcast is not possible). To avoid
 * this, a class should be defined for each particular scheduling event, but in
 * each of these classes the accept method would be the same. To avoid this
 * issue, the particular VisitableSchedulingEvent classes are produced at
 * compile time, the definition of their visit method is always the same but the
 * actual types differ, plus, when the this pointer is used, its type is
 * "pointer to a particular VisitableSchedulingEvent" which triggers the right
 * visit method choice. The particular visitor, of course, has to implement a
 * visit method for each VisitableSchedulingEvent, that is, one for each value
 * in the SchedulingEventType value set.
 * @see Visitor, Event, SchedulingEventType
 **/
template <enum SchedulingEventType> class VisitableSchedulingEvent :
    public Event<unsigned int, unsigned int>,
    public VisitorAcceptor
{
    public:
        VisitableSchedulingEvent
            (
                unsigned int subjectToSet,
                unsigned int instantToSet
            )
            : Event<unsigned int, unsigned int>(subjectToSet, instantToSet){}
        virtual void accept(Visitor* visitor)
        {
            SchedulingEventVisitor* schedulingEventVisitor =
                dynamic_cast<SchedulingEventVisitor*>(visitor);
            assert(schedulingEventVisitor != NULL);
            schedulingEventVisitor->visit(this);
        }
};

#endif
