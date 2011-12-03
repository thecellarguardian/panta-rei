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

#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

/**
 * @class CommandInterpreter
 * @brief Brief.
 * Long explaination.
 **/

template <typename Grammar> class CommandInterpreter
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
                            Grammar
                        >
                    ::value
                )
            );
        std::string command;
        const std::string welcomeMessage;
    public:
    	CommandInterpreter(std::string welcomeMessageToSet)
    		: welcomeMessage(welcomeMessageToSet)
        void prompt()
    	{
    		std::cout << welcomeMessage << std::endl;
    		std::string command;
    		while(true)
    		{
    			std::cout << ">> ";
    			std::cin >> command;
    			try
    			{
    				execute(command);
    			}
    			catch(ExitException& exit)
    			{
    				break;
    			}
    			catch(std::exception& caughtException)
    			{
    				std::cout << caughtException.what() << std::endl;
    			}
    		}
    	}
}

#endif
