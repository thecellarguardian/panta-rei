#include "CommandInterpreter.h"
#include <string>
#include <iostream>

void f()
{
    std::cout << "f" << std::endl;
}

void g()
{
    std::cout << "g" << std::endl;
}

class PantaReiGrammar :
    public boost::spirit::qi::grammar
        <std::string::const_iterator, boost::spirit::ascii::space_type>
{
    public:
    PantaReiGrammar() : PantaReiGrammar::base_type(start)
    {
        command =
                //createStatement                          |
                //setStatement                             |
                //str_p("simulate")[f] |
                //str_p("help")[f]     |
                boost::spirit::qi::double_[f]
            ;
        start =
            command |
            boost::spirit::qi::lit("ciao")[g]
            ;
    }
    boost::spirit::qi::rule<std::string::const_iterator, boost::spirit::ascii::space_type> start;
    boost::spirit::qi::rule<std::string::const_iterator, boost::spirit::ascii::space_type> command;
};

int main()
{
    CommandInterpreter<PantaReiGrammar> c("<<>>");
    c.prompt();

    return 0;
}
