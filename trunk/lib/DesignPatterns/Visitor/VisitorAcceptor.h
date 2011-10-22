/**
 * @file VisitorAcceptor.h
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

#include "Visitor.h"

#ifndef VISITOR_ACCEPTOR_H
#define VISITOR_ACCEPTOR_H

/**
 * @class VisitorAcceptor
 * @brief Acceptor interface in the Visitor design pattern.
 * A VisitorAcceptor accepts the visit from a Visitor and calls, on the accepted
 * Visitor, the appropriate method for handling the objects of its class.
 * @see "Visitor design pattern", Visitor.
 **/
class VisitorAcceptor
{
    public:
        virtual void accept(Visitor* visitor) = 0;
};

#endif
