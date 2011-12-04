#include "CommandInterpreter.h"
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

class wrappingClass
{
    public:
        void parametri(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
        {
            std::cout << a << b << c << d << std::endl;
        }
};

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


int main()
{
    CommandInterpreter< PantaReiSyntax<std::string::const_iterator> > c("<<>>");
    c.prompt();
    return 0;
}
