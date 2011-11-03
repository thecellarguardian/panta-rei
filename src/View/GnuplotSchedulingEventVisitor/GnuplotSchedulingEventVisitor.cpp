/**
 * @file GnuplotSchedulingEventVisitor.cpp
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

#include "GnuplotSchedulingEventVisitor.h"

GnuplotSchedulingEventVisitor::GnuplotSchedulingEventVisitor() : plotter("lines")
{}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<ARRIVAL>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    while(arrivalInstants[subject].size() < instant + 1)
    {
        arrivalInstants[subject].push_back(0);
    }
    arrivalInstants[subject][instant] = subject;
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<PENDING_ARRIVAL>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    while(pendingArrivalInstants[subject].size() < instant + 1)
    {
        pendingArrivalInstants[subject].push_back(0);
    }
    pendingArrivalInstants[subject][instant] = subject;
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<DEADLINE_MISS>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    while(deadlineMissInstants[subject].size() < instant + 1)
    {
        deadlineMissInstants[subject].push_back(0);
    }
    deadlineMissInstants[subject][instant] = subject;
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<END_OF_COMPUTATION>* event)

{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    while(endOfComputationInstants.size() < instant + 1)
    {
        endOfComputationInstants.push_back(0);
    }
    endOfComputationInstants[instant] = subject;
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<SCHEDULE>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    while(scheduleInstants.size() < instant + 1)
    {
        scheduleInstants.push_back(0);
    }
    scheduleInstants[instant] = subject;
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<PREEMPTION_ORIGIN>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    while(preemptionOriginInstants.size() < instant + 1)
    {
        preemptionOriginInstants.push_back(0);
    }
    preemptionOriginInstants[instant] = subject;
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<PREEMPTION_DESTINATION>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    while(preemptionDestinationInstants.size() < instant + 1)
    {
        preemptionDestinationInstants.push_back(0);
    }
    preemptionDestinationInstants[instant] = subject;
}

void GnuplotSchedulingEventVisitor::plot()
{
    plotter.set_style("points");
    for(
            std::map< unsigned int, std::vector<unsigned int> >::iterator i = arrivalInstants.begin();
            i != arrivalInstants.end();
            i++
        )
    {
        plotter.plot_x((*i).second, "Arrival time for task i");
    }
}
