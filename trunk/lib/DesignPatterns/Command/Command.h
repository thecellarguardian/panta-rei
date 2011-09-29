/**
 * @file Command.h
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

#ifndef COMMAND_H
#define COMMAND_H

/**
 * @class Command
 * @brief This class models a command.
 * A command is an object that knows how to perform a particular operation.
 * The Command class defines the command interface, execute(). This pattern
 * allows perfect separation between the View and the Control module: the View
 * module can ignore the command operations, it has just to connect the user
 * events to the proper command object, while the Control module, composed by
 * commands, implements the permitted operations. A particular command can be
 * implemented by derivation from Command, and can refer any useful context
 * (proper initialization is needed).
 * @see Command Design Pattern.
 **/
class Command
{
    public:
        virtual ~Command(){}
        virtual void execute();
};

#endif
