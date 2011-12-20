/**
 * @file Prototype.h
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

#ifndef PROTOTYPE_H
#define PROTOTYPE_H

/**
 * @class Prototype
 * @brief The Prototype Design Pattern.
 * This Design Pattern provides the implementor with a method, clone, which
 * has to be implemented to return a new copy of the callee object.
 * @tparam Implementor The implementor type.
 **/
template <typename Implementor> class Prototype
{
	public:
		/**
		* The method is aimed to return a pointer to a new Implementor object.
		* Notice that the actual type of the new object returned may be different
		* (as an example, if the implementor class is a Base class, and it leaves
		* the actual implementation to its Derived class, when clone is called
		* on a Derived object it will return a pointer to Base which points to a
		* new clone).)
		**/
		virtual Implementor* clone() = 0;
};

#endif
