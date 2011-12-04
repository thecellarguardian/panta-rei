/*=============================================================================
    Copyright (c) 2002-2009 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A parser for arbitrary tuples. This example presents a parser
//  for an employee structure.
//
//  [ JDG May 9, 2007 ]
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <complex>
#include <typeinfo>

void findItOut(std::type_info& a)
{
    std::cout << a.name() << std::endl;
}

void f()
{
    std::cout << "f" << std::endl;
}

void g()
{
    std::cout << "g" << std::endl;
}

void h()
{
    std::cout << "h" << std::endl;
}

void parametri(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    std::cout << a << b << c << d << std::endl;
}

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
template <typename Iterator>
class PantaReiSyntax : public qi::grammar<Iterator, ascii::space_type>
{
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
                boost::phoenix::bind(&parametri, boost::spirit::qi::_1, boost::spirit::qi::_2, boost::spirit::qi::_3, boost::spirit::qi::_4)
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
    boost::spirit::qi::rule
        <
            Iterator,
            boost::spirit::ascii::space_type
        >
        command
    ;
    boost::spirit::qi::rule
        <
            Iterator,
            boost::spirit::ascii::space_type
        >
        createStatement
    ;
    boost::spirit::qi::rule
        <
            Iterator,
            boost::spirit::ascii::space_type
        >
        setStatement
    ;
    boost::spirit::qi::rule
        <
            Iterator,
            boost::spirit::ascii::space_type
        >
        objectStatement
    ;
    boost::spirit::qi::rule
        <
            Iterator,
            boost::spirit::ascii::space_type
        >
        propertyStatement
    ;
    boost::spirit::qi::rule
        <
            Iterator,
            boost::spirit::ascii::space_type
        >
        schedulingAlgorithm
    ;
};

////////////////////////////////////////////////////////////////////////////
//  Main program
////////////////////////////////////////////////////////////////////////////
int main()
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef PantaReiSyntax<iterator_type> PantaReiSyntax;

    PantaReiSyntax g; // Our grammar
    std::string str;
    while (getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;
        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        bool r = phrase_parse(iter, end, g, space);
        if (r && iter == end)
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "-------------------------\n";
        }
        else
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye... :-) \n\n";
    return 0;
}

