/**
 * @file PantaReiLanguage.h
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
 
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <iostream>
#include <string>
#include "../../Model/SchedulingSimulation/SchedulingSimulation.h"
#include "../../Model/Scheduler/RateMonotonic/RateMonotonic.h"
#include "../../Model/Scheduler/DeadlineMonotonic/DeadlineMonotonic.h"
#include "../../Model/Scheduler/EarliestDeadlineFirst/EarliestDeadlineFirst.h"

#ifndef PANTA_REI_LANGUAGE_H
#define PANTA_REI_LANGUAGE_H

/**
 * @class PantaReiLanguage
 * @brief A simple language to control the application.
 * PantaReiLanguage defines the language to interact with the application using
 * EBNF through the Boost Spirit Qi parsing framework. While the language syntax
 * is defined here, the language semantics are defined into the
 * SchedulingSimulation class.
 **/

//TODO higher abstraction of the language concept, something like:
//a Language is something composed by a Syntax, a Semantic and relations between
//those objects.

class PantaReiLanguage :
    public
    boost::spirit::qi::grammar
        <
            std::string::const_iterator,
            boost::spirit::ascii::space_type
        >
{
    SchedulingSimulation simulationEnvironment;
    public:
    PantaReiLanguage() : PantaReiLanguage::base_type(command)
    {
        command %=
            createStatement                    |
            setStatement                       |
            boost::spirit::qi::lit("simulate")
                [
                    boost::phoenix::bind
                        (
                            &SchedulingSimulation::simulate,
                            simulationEnvironment
                        )
                ]
            |
            boost::spirit::qi::lit("help")     |
            boost::spirit::qi::lit("quit")
        ;
        createStatement %=
            boost::spirit::qi::lit("create") >>
            objectStatement
        ;
        setStatement %=
            boost::spirit::qi::lit("set") >>
            propertyStatement
        ;
        objectStatement %=
            (
                boost::spirit::qi::lit("periodic") >>
                boost::spirit::qi::lit("task")     >>
                boost::spirit::qi::uint_           >>
                boost::spirit::qi::uint_           >>
                boost::spirit::qi::uint_           >>
                boost::spirit::qi::uint_
            )
            [
                boost::phoenix::bind
                    (
                        &SchedulingSimulation::createPeriodicTask,
                        simulationEnvironment,
                        boost::spirit::qi::_1,
                        boost::spirit::qi::_2,
                        boost::spirit::qi::_3,
                        boost::spirit::qi::_4
                    )
            ]
        ;
        propertyStatement %=
            (
                boost::spirit::qi::lit("simulation") >>
                boost::spirit::qi::lit("length")     >>
                boost::spirit::qi::uint_
            )
                [
                    boost::phoenix::bind
                        (
                            &SchedulingSimulation::setSimulationLength,
                            simulationEnvironment,
                            boost::spirit::qi::_1
                        )
                ]
            |
            (
                boost::spirit::qi::lit("scheduler") >>
                schedulingAlgorithm
            )
        ;
        schedulingAlgorithm %=
            boost::spirit::qi::lit("PRM")
                [
                    boost::phoenix::bind
                        (
                            &SchedulingSimulation::
                                setSchedulingAlgorithm<RateMonotonic>,
                            simulationEnvironment,
                            true
                        )
                ]
            |
            boost::spirit::qi::lit("NPRM")
                [
                    boost::phoenix::bind
                        (
                            &SchedulingSimulation::
                                setSchedulingAlgorithm<RateMonotonic>,
                            simulationEnvironment,
                            false
                        )
                ]
            |
            boost::spirit::qi::lit("PDM")
                [
                    boost::phoenix::bind
                        (
                            &SchedulingSimulation::
                                setSchedulingAlgorithm<DeadlineMonotonic>,
                            simulationEnvironment,
                            true
                        )
                ]
            |
            boost::spirit::qi::lit("NPDM")
                [
                    boost::phoenix::bind
                        (
                            &SchedulingSimulation::
                                setSchedulingAlgorithm<DeadlineMonotonic>,
                            simulationEnvironment,
                            false
                        )
                ]
            |
            boost::spirit::qi::lit("PEDF")
                [
                    boost::phoenix::bind
                        (
                            &SchedulingSimulation::
                                setSchedulingAlgorithm<EarliestDeadlineFirst>,
                            simulationEnvironment,
                            true
                        )
                ]
            |
            boost::spirit::qi::lit("NPEDF")
                [
                    boost::phoenix::bind
                        (
                            &SchedulingSimulation::
                                setSchedulingAlgorithm<EarliestDeadlineFirst>,
                            simulationEnvironment,
                            false
                        )
                ]
        ;
    }
    boost::spirit::qi::rule
        <
            std::string::const_iterator,
            boost::spirit::ascii::space_type
        >
        command,
        createStatement,
        setStatement,
        objectStatement,
        propertyStatement,
        schedulingAlgorithm
    ;
};

#endif
