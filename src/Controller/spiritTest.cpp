#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <iostream>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

class Interpreter
{
    
};

void f()
{
    std::cout << "ciao" << std::endl;
}

template <typename Iterator>
    int parse_integer(Iterator first, Iterator last)
    {
        using boost::spirit::qi::double_;
        using boost::spirit::qi::_1;
        using boost::spirit::qi::phrase_parse;
        using boost::spirit::ascii::space;
        using boost::phoenix::ref;
        int rN = 0;
        bool r = phrase_parse(first, last,
            //  Begin grammar
            (
                    "(" >> boost::spirit::qi::int_[ref(rN) = _1] >> ')' |
                    boost::spirit::qi::string("ciao")[f]
            ),
            //  End grammar
            space);

        if (!r || first != last) // fail if we did not get a full match
            return -1;
        
        return rN;
    }

//OK, IT WORKS!F

int main()
{
    std::string s;
    std::cin >> s;
    
    std::cout << parse_integer(s.begin(), s.end()) << std::endl;
    return 0;
}
