/**
 * @file SchedulingEventVisitor.h
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
#include "SchedulingEventType.h"
#include <iostream>

template <enum SchedulingEventType> class VisitableSchedulingEvent;

#ifndef SCHEDULING_EVENT_VISITOR_H
#define SCHEDULING_EVENT_VISITOR_H

/**
 * @class SchedulingEventVisitor
 * @brief A generic SchedulingEvent visitor.
 * This interface overloads a visit method for each possible
 * VisitableSchedulingEvent.
 * @see Visitor, Event, SchedulingEventType
 **/
class SchedulingEventVisitor : public Visitor
{
    public:
    	virtual void visit(VisitableSchedulingEvent<ARRIVAL>*) = 0;
        virtual void visit(VisitableSchedulingEvent<PENDING_ARRIVAL>*) = 0;
    	virtual void visit(VisitableSchedulingEvent<END_OF_COMPUTATION>*) = 0;
    	virtual void visit(VisitableSchedulingEvent<DEADLINE_MISS>*) = 0;
    	virtual void visit(VisitableSchedulingEvent<SCHEDULE>*) = 0;
    	virtual void visit(VisitableSchedulingEvent<PREEMPTION_ORIGIN>*) = 0;
        virtual void visit(VisitableSchedulingEvent<PREEMPTION_DESTINATION>*) = 0;
};

#endif
