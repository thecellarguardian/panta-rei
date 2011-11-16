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

#ifndef SCHEDULING_SIMULATION_H
#define SCHEDULING_SIMULATION_H

/**
 * @class SchedulingSimulation
 * @brief The scheduling simulation environment.
 * This class encapsulates the creation and link logic of all the objects
 * involved into the simulation, and provides a command interface to modify each
 * simulation property.
 **/

class SchedulingSimulation
{
    private:
        Timer timer;
        boost::shared_ptr<SystemQueuesManager>
        boost::shared_ptr<Activator> activator;
        boost::shared_ptr<Scheduler> scheduler;
        std::vector< boost::shared_ptr<Task> > tasks;
        History< Event<unsigned int, unsigned int> >
        boost::shared_ptr<SchedulingEventVisitor> simulationVisitor;
    public:
        SchedulingSimulation();
        SchedulingSimulation
        (
            int simulationLength,
            boost::shared_ptr<Scheduler> schedulerToSet,
            boost::shared_ptr<SchedulingEventVisitor> simulationVisitorToSet
        );
        void createPeriodicTask
        (
            int arrivalTime,
            int computationTime,
            int relativeDeadline,
            int period
        );
        //TODO void removeTask ??
        void setSimulationLength(int simulationLengthToSet);
        template <typename SchedulingAlgorithm> void setSchedulingAlgorithm();
        void simulate();
};
