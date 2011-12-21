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
#include <cassert>
#include "ExitException.h"
#include "BadSyntaxException.h"
#include "../StaticLog/StaticLog.h"

#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

/**
 * @class CommandInterpreter
 * @brief Generic command interpreter.
 * A generic command interpreter. It's built using the Boost Spirit Qi
 * framework. The particular grammar and behaviour can be defined in a Grammar
 * class inheriting from boost::spirit::qi::grammar, where it can be described
 * using an EBNF-fashioned C++, toghether with the related semantic actions.
 * The interpreted language has to be a Spirit Qi grammar, an
 * explicit compile time check is done to verify this property.
 * @see Boost Spirit Qi framework, Boost Static Assert.
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
        /**<
         * The interpreted language grammar.
         **/
        const std::string welcomeMessage;
        /**<
         * A welcome message to be print when in interactive mode.
         **/
        std::istream* sourceSource;
        /**<
         * The source code to interpret.
         **/
        bool interactiveFlag;
        /**<
         * A flag to distinguish the two cases of interactive or batch
         * interpreter.
         **/
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
        /**
         * This is the main section of the comman interpreter, a loop in which
         * every statement is caught and interpreted through the specifie
         * grammar.
         **/
        void run()
        {
            assert(StaticLog::log["error"] != NULL);
            std::ostream* errorLog = StaticLog::log["error"];
            std::string statement;
            if(interactiveFlag)
            {
                std::cout << welcomeMessage << std::endl;
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
                    (*errorLog) << caughtException.what() << std::endl;
                    if(!interactiveFlag)
                    {
                        break;                        
                    }
                }
                catch(std::exception& caughtException)
                {
                    std::cerr << caughtException.what() << std::endl;
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
