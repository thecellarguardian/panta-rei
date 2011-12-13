/**
 * @file CommandInterpreter.h
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
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <iostream>
#include <exception>
#include "ExitException.h"
#include "BadSyntaxException.h"

#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

/**
 * @class CommandInterpreter
 * @brief Generic command interpreter.
 * A generic command interpreter. It's built using the Boost Spirit Qi
 * framework. The particular grammar and behaviour can be defined in a Grammar
 * class inheriting drom boost::spirit::qi::grammar, where it can be described
 * using an EBNF-fashioned C++, toghether with the related semantic actions.
 **/

template <typename Language> class CommandInterpreter
{
    private:
        BOOST_STATIC_ASSERT
            (
                (
                    boost::is_base_of
                        <
                            boost::spirit::qi::grammar
                                <
                                    std::string::const_iterator,
                                    boost::spirit::ascii::space_type
                                >,
                            Language
                        >
                    ::value
                )
            );
        Language grammar;
        const std::string welcomeMessage;
        std::istream* sourceSource;
        bool interactiveFlag;
    public:
        CommandInterpreter
            (
                std::string welcomeMessageToSet,
                std::istream* sourceSourceToSet
            )
            :
            welcomeMessage(welcomeMessageToSet),
            sourceSource(sourceSourceToSet),
            interactiveFlag(sourceSource == &std::cin)
            {}
        void run()
        {
            std::cout << welcomeMessage << std::endl;
            std::string statement;
            if(interactiveFlag)
            {
                std::cout << ">> ";
            }
            while(getline(*sourceSource, statement))
            {
                try
                {
                    std::string::const_iterator statementBegin = statement.begin();
                    std::string::const_iterator statementEnd = statement.end();
                    if
                        (
                            !
                            phrase_parse
                                (
                                    statementBegin,
                                    statementEnd,
                                    grammar,
                                    boost::spirit::ascii::space
                                )
                        )
                    {
                        BadSyntaxException badSyntax(statement);
                        throw badSyntax;
                    }
                }
                catch(ExitException& exitSignal)
                {
                    break;
                }
                catch(BadSyntaxException& caughtException)
                {
                    std::cout << caughtException.what() << std::endl;
                    if(!interactiveFlag)
                    {
                        break;                        
                    }
                }
                if(interactiveFlag)
                {
                    std::cout << ">> ";
                }
            }
        }
};

#endif
