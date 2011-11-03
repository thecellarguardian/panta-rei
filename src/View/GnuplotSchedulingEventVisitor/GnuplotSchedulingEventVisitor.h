/**
 * @file GnuplotSchedulingEventVisitor.h
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

#include "../../Model/SchedulationEvents/SchedulingEventVisitor.h"
#include "../../../lib/gnuplot-cpp/gnuplot_i.hpp"
#include <vector>
#include <map>

#ifndef GNUPLOT_SCHEDULING_EVENT_VISITOR_H
#define GNUPLOT_SCHEDULING_EVENT_VISITOR_H

/**
 * @class
 * @brief
 * @see Visitor, Event, SchedulingEventType
 **/
class GnuplotSchedulingEventVisitor : public SchedulingEventVisitor
{
    private:
        Gnuplot plotter;
        std::map< unsigned int, std::vector<unsigned int> > arrivalInstants;
        std::map< unsigned int, std::vector<unsigned int> >
            pendingArrivalInstants;
        std::map< unsigned int, std::vector<unsigned int> >
            deadlineMissInstants;
        std::vector<unsigned int> endOfComputationInstants;
        std::vector<unsigned int> scheduleInstants;
        std::vector<unsigned int> preemptionOriginInstants;
        std::vector<unsigned int> preemptionDestinationInstants;
    public:
        GnuplotSchedulingEventVisitor();
        void visit(VisitableSchedulingEvent<ARRIVAL>*);
        void visit(VisitableSchedulingEvent<PENDING_ARRIVAL>*);
        void visit(VisitableSchedulingEvent<DEADLINE_MISS>*);
        void visit(VisitableSchedulingEvent<END_OF_COMPUTATION>*);
        void visit(VisitableSchedulingEvent<SCHEDULE>*);
        void visit(VisitableSchedulingEvent<PREEMPTION_ORIGIN>*);
        void visit(VisitableSchedulingEvent<PREEMPTION_DESTINATION>*);
        void plot();
};

#endif
