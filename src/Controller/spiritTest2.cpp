/*=============================================================================
    Copyright (c) 2001-2003 Andy Elvey
    Copyright (c) 2001-2003 Dan Nuffer
    http://spirit.sourceforge.net/

    Permission to copy, use, modify, sell and distribute this software is
    granted provided this copyright notice appears in all copies. This
    software is provided "as is" without express or implied warranty, and
    with no claim as to its suitability for any purpose.
=============================================================================*/
//
//  A very simple parser grammar .
//  This parser parses a simple polynomial expression ( of the form
//  aX^2 + bX^3 + ...  ) .
//
// Uses:  The Spirit parser framework, which was written by
//  Joel de Guzman
//

//#define BOOST_SPIRIT_DEBUG  //$$$ DEFINE THIS WHEN DEBUGGING $$$//

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

///////////////////////////////////////////////////////////////////////////////
using namespace boost::spirit;
using namespace boost::spirit::classic;
using namespace std;

void f(double d)
{
    std::cout << "f()" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
//  Start grammar definition
//----------------------------------------------------------------------------

struct PantaReiGrammar :
    public boost::spirit::classic::grammar<PantaReiGrammar>
{
    template <typename Scanner> struct definition
    {
        rule<Scanner> command;
        //rule<Scanner> createStatement;
        //rule<Scanner> setStatement;
        //rule<Scanner> object;
        //rule<Scanner> property;
        //rule<Scanner> schedulingAlgorithm;
        definition(PantaReiGrammar const&)
        {
            command =
                //createStatement                          |
                //setStatement                             |
                //str_p("simulate")[f] |
                //str_p("help")[f]     |
                double_[&f]
            ;
        }
        rule<Scanner> const& start() const
        {
            return command;
        }
    };
};


int
main(int /*argc*/, char** /*argv[]*/)
{
    PantaReiGrammar g;
    string str;
    while (getline(cin, str))
    {
        if (str[0] == 'q' || str[0] == 'Q')
            break;

        if (parse(str.c_str(), g, space_p).full)
        {
            cout << "parsing succeeded\n";
        }
        else
        {
            cout << "parsing failed\n";
        }
    }

    cout << "Bye... :-) \n\n";
    return 0;
}
