/**
 * @file Visitor.h
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

#ifndef VISITOR_H
#define VISITOR_H

class VisitorAcceptor;

/**
 * @class Visitor
 * @brief Visitor concept in the Visitor design pattern.
 * A particular Visitor interface implementor has to deal with a particular
 * family of VisitorAcceptor implementors, and has to expose a visit method for
 * each type in that family. Of course, the VisitorAcceptor family should not
 * change frequently, since that change would reflect directly on the related
 * Visitor interface. Each visit method is dedicated to a particular class and
 * is called when an acceptor accepts a visitor: the visit method has to "visit"
 * the acceptor (which has been passed by reference or pointer) and perform a
 * particular task, depending on the purpose of the particular visitor.
 * A typical example is a parse tree: each node has a particular type
 * (BinaryExpression, Constant, Identifier...) but they all implement the
 * VisitorAcceptor interface. When they accept a Visitor, they call back the
 * dedicated method the visitor exposes (such as visit(BinaryExpression*),
 * visit(Constant*)...), and the visitor (which is a particular Visitor
 * implementor) performs different operations depending on its own purpose 
 * and the acceptor type (code generation, pretty print, statistics...).
 * @see "Visitor design pattern."
 **/
class Visitor
{
    public:
        virtual void defaultVisit(VisitorAcceptor* visitorAcceptor){};
};

#endif
