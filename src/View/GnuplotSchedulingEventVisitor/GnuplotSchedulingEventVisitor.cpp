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

void GnuplotSchedulingEventVisitor::updateTaskIDRange(unsigned int subject)
{
    if(subject > highestTaskID)
    {
        highestTaskID = subject;
        return;
    }
}

GnuplotSchedulingEventVisitor::GnuplotSchedulingEventVisitor() : plotter("steps")
{
    plotter.set_ylabel("Time");
    plotter.set_xlabel("Tasks");
    plotter.cmd("set xtics 1");
    plotter.cmd("set ytics 1,1");
    plotter.set_grid();
    lowestTaskID = 1;
    highestTaskID = 1;
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<ARRIVAL>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    arrivalInstants[subject].push_back(instant);
    updateTaskIDRange(subject);
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<PENDING_ARRIVAL>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    arrivalInstants[subject].push_back(instant);
    updateTaskIDRange(subject);
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<DEADLINE_MISS>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    deadlineMissInstants[subject].push_back(instant);
    updateTaskIDRange(subject);
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<END_OF_COMPUTATION>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    endOfComputationInstants.push_back(instant);
    endingTasks.push_back(subject);
    updateTaskIDRange(subject);
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<SCHEDULE>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    if(subject != 0)
    {
        scheduleInstants.push_back(instant);
        scheduledTasks.push_back(subject);
        updateTaskIDRange(subject);
    }
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<PREEMPTION_ORIGIN>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    preemptionOriginInstants.push_back(instant);
    preemptingOutTasks.push_back(subject);
    updateTaskIDRange(subject);
}

void GnuplotSchedulingEventVisitor::visit(VisitableSchedulingEvent<PREEMPTION_DESTINATION>* event)
{
    unsigned int subject = event->getSubject();
    unsigned int instant = event->getInstant();
    preemptionDestinationInstants.push_back(instant);
    preemptingInTasks.push_back(subject);
    updateTaskIDRange(subject);
}

void GnuplotSchedulingEventVisitor::plot()
{
    plotter.set_style("points");
    std::cout << "lowest: " << lowestTaskID << ", highest: " << highestTaskID << std::endl;
    plotter.set_yrange(lowestTaskID, 2*highestTaskID);
    for
        (
            std::map< unsigned int, std::vector<unsigned int> >::iterator i = arrivalInstants.begin();
            i != arrivalInstants.end();
            i++
        )
    {
        std::string legend("Arrival time for task ");
        legend.append(boost::lexical_cast<std::string>((*i).first));
        std::vector<unsigned int> task((*i).second.size(), (*i).first);
        plotter.plot_xy((*i).second, task, legend);
    }
    for
        (
            std::map< unsigned int, std::vector<unsigned int> >::iterator i = deadlineMissInstants.begin();
            i != deadlineMissInstants.end();
            i++
        )
    {
        std::string legend("Deadline miss for task ");
        legend.append(boost::lexical_cast<std::string>((*i).first));
        std::vector<unsigned int> task((*i).second.size(), (*i).first);
        plotter.plot_xy((*i).second, task, legend);
    }
    plotter.plot_xy(endOfComputationInstants, endingTasks, "End of computation");
    plotter.plot_xy(preemptionOriginInstants, preemptingOutTasks, "Preemption origin");
    plotter.plot_xy(preemptionDestinationInstants, preemptingInTasks, "Preemption origin");
    plotter.set_style("steps");
    plotter.plot_xy(scheduleInstants, scheduledTasks, "Schedule");
    char a = 'a';
    std::cin >> a;
}
