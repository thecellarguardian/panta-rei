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
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <complex>
#include <typeinfo>

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
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
template <typename Iterator>
class PantaReiSyntax : public qi::grammar<Iterator, ascii::space_type>
{
    wrappingClass wC;
    public:
    PantaReiSyntax() : PantaReiSyntax::base_type(command)
    {
        command %=
            createStatement                    |
            setStatement                       |
            boost::spirit::qi::lit("simulate")[f] |
            boost::spirit::qi::lit("help")[g]     |
            boost::spirit::qi::lit("quit")[h]
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
                boost::spirit::qi::lit("task") >>
                boost::spirit::qi::uint_ >>
                boost::spirit::qi::uint_ >>
                boost::spirit::qi::uint_ >>
                boost::spirit::qi::uint_
            )
            [
                //boost::phoenix::bind(&parametri, boost::spirit::qi::_1, boost::spirit::qi::_2, boost::spirit::qi::_3, boost::spirit::qi::_4)
                boost::phoenix::bind(&wrappingClass::parametri, wC, boost::spirit::qi::_1, boost::spirit::qi::_2, boost::spirit::qi::_3, boost::spirit::qi::_4)
            ]
        ;
        propertyStatement %=
            (
                boost::spirit::qi::lit("simulation") >>
                boost::spirit::qi::lit("length") >>
                boost::spirit::qi::uint_
            )
            [
                //boost::bind(&parametri, _2, 0, 0, 0)
                f
            ]
            |
            (
                boost::spirit::qi::lit("scheduler") >>
                schedulingAlgorithm
            )
        ;
        schedulingAlgorithm %=
            boost::spirit::qi::lit("RM")  |
            boost::spirit::qi::lit("DM")  |
            boost::spirit::qi::lit("EDF")
        ;
    }
    boost::spirit::qi::rule<Iterator, boost::spirit::ascii::space_type>
        command,
        createStatement,
        setStatement,
        objectStatement,
        propertyStatement,
        schedulingAlgorithm
    ;
};

#endif
