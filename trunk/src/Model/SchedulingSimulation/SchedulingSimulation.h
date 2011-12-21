/**
 * @file SchedulingSimulation.h
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

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/shared_ptr.hpp>
#include "../Timer/Timer.h"
#include "../SystemQueuesManager/SystemQueuesManager.h"
#include "../Activator/Activator.h"
#include "../Scheduler/Scheduler.h"
#include "../Task/Task.h"
#include "../History/History.h"
#include "../../../lib/DesignPatterns/Visitor/VisitorAcceptor.h"
#include "../../../lib/DesignPatterns/Visitor/Visitor.h"

#ifndef SCHEDULING_SIMULATION_H
#define SCHEDULING_SIMULATION_H

/**
 * @class SchedulingSimulation
 * 
 * @brief The scheduling simulation environment.
 * 
 * This class encapsulates the creation and link logic of all the objects
 * involved into the simulation, and provides a command interface to modify each
 * simulation property.
 **/
class SchedulingSimulation : public VisitorAcceptor
{
    private:
        Timer timer;
        boost::shared_ptr<SystemQueuesManager> systemQueues;
        boost::shared_ptr<Activator> activator;
        boost::shared_ptr<Scheduler> scheduler;
        std::list< boost::shared_ptr<Task> > tasks;
        History< Event<unsigned int, unsigned int> > history;
        unsigned int taskIDGenerator;
        bool simulationDone;
    public:
        SchedulingSimulation();
        SchedulingSimulation
        (
            int simulationLength,
            boost::shared_ptr<Scheduler> schedulerToSet
        );
        unsigned int createPeriodicTask
        (
            unsigned int arrivalTime,
            unsigned int computationTime,
            unsigned int relativeDeadline,
            unsigned int period
        );
        //TODO void removeTask ??
        void setSimulationLength(unsigned int simulationLengthToSet);
        /**
         * SchedulingAlgorithm must extend Scheduler.
         **/
        template <typename SchedulingAlgorithm> void setSchedulingAlgorithm
            (
                bool preemptiveFlag
            )
        {
            BOOST_STATIC_ASSERT
            (
                (boost::is_base_of<Scheduler, SchedulingAlgorithm>::value)
            );
            //TODO: the registration mechanics are awful. The current situation
            //is the following:
            //the new scheduler has to replace exactly the old one in the timer's
            //attachedObservers list, but when the new scheduler is created it
            //autonomously attaches itself to the timer, so it's necessary first
            //to remove it from the timer attacherObservers list
            if(scheduler.get() != NULL)
            {
                scheduler->detach(&history);
            }
            boost::shared_ptr<Scheduler>
                newScheduler
                    (
                        new SchedulingAlgorithm
                            (
                                preemptiveFlag,
                                systemQueues,
                                &timer, //
                                activator
                            )
                    );
            timer.detach(newScheduler.get()); //<= here it is
            timer.substitute(scheduler.get(), newScheduler.get());
            scheduler = newScheduler;
        }
        /**
         * This method starts the simulation, whose scheduling events are
         * recorder into the history for further manipulation.
         **/
        void simulate();
        void clear();
        /**
         * SchedulingSimulation is a VisitorAcceptor, it propagates the accept
         * method of the internal History.
         **/
        void accept(Visitor* visitor);
};

#endif
