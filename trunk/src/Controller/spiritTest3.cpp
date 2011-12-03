#include <boost/spirit/include/qi.hpp>
#include <boost/config/warning_disable.hpp>
#include <iostream>
#include <string>

void f()
{
    std::cout << "f" << std::endl;
}

void g()
{
    std::cout << "g" << std::endl;
}

template <typename Iterator>
struct PantaReiGrammar : boost::spirit::qi::grammar<Iterator, /*valueType,*/ boost::spirit::ascii::space_type>
{
    PantaReiGrammar() : PantaReiGrammar::base_type(start)
    {
        namespace qi = boost::spirit::qi;
        namespace ascii = boost::spirit::ascii;
        using qi::int_;
        using qi::lit;
        using qi::double_;
        using qi::lexeme;
        using ascii::char_;
        command =
                //createStatement                          |
                //setStatement                             |
                //str_p("simulate")[f] |
                //str_p("help")[f]     |
                double_[f]
            ;
        start =
            command |
            lit("ciao")[g]
            ;
    }
    boost::spirit::qi::rule<Iterator, /*ruleType,*/ boost::spirit::ascii::space_type> start;
    boost::spirit::qi::rule<Iterator, /*ruleType,*/ boost::spirit::ascii::space_type> command;
};

int main()
{
    using boost::spirit::ascii::space;
    PantaReiGrammar<std::string::const_iterator> g; // Our grammar
    std::string str;
    while (getline(std::cin, str))
    {
        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        bool r = boost::spirit::qi::phrase_parse(iter, end, g, space);
    }
    std::cout << "Bye... :-) \n\n";
    return 0;
}
