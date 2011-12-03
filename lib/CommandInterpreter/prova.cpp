#include <boost/bind.hpp>
#include "CommandInterpreter.h"

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

class PantaReiSyntax :
    public boost::spirit::qi::grammar
        <std::string::const_iterator, boost::spirit::ascii::space_type>
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
        setStatement =
            boost::spirit::qi::lit("set") >>
            propertyStatement
        ;
        objectStatement %=
            (
                boost::spirit::qi::lit("periodic")/* >>
                boost::spirit::qi::uint_ >>
                boost::spirit::qi::uint_ >>
                boost::spirit::qi::uint_ >>
                boost::spirit::qi::uint_*/
            )
            [
                //boost::bind(&parametri, _2, _3, _4, _5)
                f
            ]
        ;
        propertyStatement =
            (
                boost::spirit::qi::lit("simulation length") >>
                boost::spirit::qi::uint_
            )
            /*[
                boost::bind(&parametri, _2, 0, 0, 0)
            ]*/
            |
            (
                boost::spirit::qi::lit("scheduler") >>
                schedulingAlgorithm
            )
        ;
        schedulingAlgorithm =
            boost::spirit::qi::lit("RM")  |
            boost::spirit::qi::lit("DM")  |
            boost::spirit::qi::lit("EDF")
        ;
    }
    boost::spirit::qi::rule
        <
            std::string::const_iterator,
            boost::spirit::ascii::space_type
        >
        command
    ;
    boost::spirit::qi::rule
        <
            std::string::const_iterator,
            boost::spirit::ascii::space_type
        >
        createStatement
    ;
    boost::spirit::qi::rule
        <
            std::string::const_iterator,
            boost::spirit::ascii::space_type
        >
        setStatement
    ;
    boost::spirit::qi::rule
        <
            std::string::const_iterator,
            boost::spirit::ascii::space_type
        >
        objectStatement
    ;
    boost::spirit::qi::rule
        <
            std::string::const_iterator,
            boost::spirit::ascii::space_type
        >
        propertyStatement
    ;
    boost::spirit::qi::rule
        <
            std::string::const_iterator,
            boost::spirit::ascii::space_type
        >
        schedulingAlgorithm
    ;
};

int main()
{
    CommandInterpreter<PantaReiSyntax> c("<<>>");
    c.prompt();

    return 0;
}
