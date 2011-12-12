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
#include "../../Model/SchedulationEvents/VisitableSchedulingEvent.h"
#include "../../../lib/gnuplot-cpp/gnuplot_i.hpp"
#include <boost/lexical_cast.hpp>
#include <vector>
#include <map>
#include <string>
#include <iostream>

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
            deadlineMissInstants;
        std::vector<unsigned int> endOfComputationInstants;
        std::vector<unsigned int> endingTasks;
        std::vector<unsigned int> scheduleInstants;
        std::vector<unsigned int> scheduledTasks;
        std::vector<unsigned int> preemptionOriginInstants;
        std::vector<unsigned int> preemptingOutTasks;
        std::vector<unsigned int> preemptionDestinationInstants;
        std::vector<unsigned int> preemptingInTasks;
        unsigned int lowestTaskID;
        unsigned int highestTaskID;
        void updateTaskIDRange(unsigned int subject)
        {
            if(subject > highestTaskID)
            {
                highestTaskID = subject;
                return;
            }
        }
    public:
    GnuplotSchedulingEventVisitor() : plotter("steps")
    {
    	plotter.set_ylabel("Time");
    	plotter.set_xlabel("Tasks");
        plotter.cmd("set xtics 1");
        plotter.cmd("set ytics 1,1");
        plotter.set_grid();
    	lowestTaskID = 1;
    	highestTaskID = 1;
    }
    void visit(VisitableSchedulingEvent<ARRIVAL>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        arrivalInstants[subject].push_back(instant);
        updateTaskIDRange(subject);
        std::cout
            << "ARRIVAL scheduling event visited"
            << std::endl;
    }
    void visit(VisitableSchedulingEvent<PENDING_ARRIVAL>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        arrivalInstants[subject].push_back(instant);
        updateTaskIDRange(subject);
        std::cout
            << "PENDING_ARRIVAL scheduling event visited"
            << std::endl;
    }
    void visit(VisitableSchedulingEvent<DEADLINE_MISS>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        deadlineMissInstants[subject].push_back(instant);
        updateTaskIDRange(subject);
        std::cout
            << "DEADLINE_MISS scheduling event visited"
            << std::endl;
    }
    void visit(VisitableSchedulingEvent<END_OF_COMPUTATION>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        endOfComputationInstants.push_back(instant);
        endingTasks.push_back(subject);
        updateTaskIDRange(subject);
        std::cout
            << "END_OF_COMPUTATION scheduling event visited"
            << std::endl;
    }
    void visit(VisitableSchedulingEvent<SCHEDULE>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        scheduleInstants.push_back(instant);
        scheduledTasks.push_back(subject);
        updateTaskIDRange(subject);
        std::cout
            << "SCHEDULE scheduling event visited"
            << std::endl;
    }
    void visit(VisitableSchedulingEvent<PREEMPTION_ORIGIN>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        preemptionOriginInstants.push_back(instant);
        preemptingOutTasks.push_back(subject);
        updateTaskIDRange(subject);
        std::cout
            << "PREEMPRION_ORIGIN scheduling event visited"
            << std::endl;
    }
    void visit(VisitableSchedulingEvent<PREEMPTION_DESTINATION>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        preemptionDestinationInstants.push_back(instant);
        preemptingInTasks.push_back(subject);
        updateTaskIDRange(subject);
        std::cout
            << "PREEMPTION_DESTINATION scheduling event visited"
            << std::endl;
    }
    void plot()
    {
        plotter.set_style("points");
        std::cout << "lowest: " << lowestTaskID << ", highest: " << highestTaskID << std::endl;
        plotter.set_yrange(0, 2*highestTaskID);
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
        if(endOfComputationInstants.size() > 0)
        {
            plotter.plot_xy
                (endOfComputationInstants, endingTasks, "End of computation");
        }
        if(preemptionOriginInstants.size() > 0)
        {
            plotter.plot_xy
                (
                    preemptionOriginInstants,
                    preemptingOutTasks,
                    "Preemption origin"
                );
        }
        if(preemptionDestinationInstants.size() > 0)
        {
            plotter.plot_xy
                (
                    preemptionDestinationInstants,
                    preemptingInTasks,
                    "Preemption destination"
                );
        }
        plotter.set_style("steps");
        if(scheduleInstants.size() > 0)
        {
            plotter.plot_xy
                (
                    scheduleInstants,
                    scheduledTasks,
                    "Schedule"
                );
        }
        plotter.plot_slope(0, 0, "IDLE");
    }
    void defaultVisit(VisitorAcceptor* visitorAcceptor)
    {
        visitorAcceptor->accept(this);
        plot();
        clear();
    }
    void clear()
    {
        arrivalInstants.erase(arrivalInstants.begin(), arrivalInstants.end());
        deadlineMissInstants.erase
            (deadlineMissInstants.begin(), deadlineMissInstants.end());
        endOfComputationInstants.erase
            (endOfComputationInstants.begin(), endOfComputationInstants.end());
        endingTasks.erase(endingTasks.begin(), endingTasks.end());
        scheduleInstants.erase(scheduleInstants.begin(), scheduleInstants.end());
        scheduledTasks.erase(scheduledTasks.begin(), scheduledTasks.end());
        preemptionOriginInstants.erase
            (preemptionOriginInstants.begin(), preemptionOriginInstants.end());
        preemptingOutTasks.erase
            (preemptingOutTasks.begin(), preemptingOutTasks.end());
        preemptionDestinationInstants.erase
            (
                preemptionDestinationInstants.begin(),
                preemptionDestinationInstants.end()
            );
        preemptingInTasks.erase
            (preemptingInTasks.begin(), preemptingInTasks.end());
        lowestTaskID = 1;
        highestTaskID = 1;
        plotter.reset_plot();
    }
};

#endif
