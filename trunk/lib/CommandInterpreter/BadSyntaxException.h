/**
 * @file BadSyntaxException.h
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

#include <stdexcept>
#include <string>

#ifndef BAD_SYNTAX_EXCEPTION
#define BAD_SYNTAX_EXCEPTION

/**
 * @class BadSyntaxException
 * @brief Syntax error exception.
 * When a badly formed command occurs, this exception is thrown.
 **/
class BadSyntaxException : public std::runtime_error
{
    public:
        BadSyntaxException(std::string badCommand)
            : std::runtime_error
                (
                    badCommand.append
                        (
                            ": Invalid syntax. Use \"help\" to see Panta Rei syntax in EBNF."
                        )
                )
                {}
};

#endif
