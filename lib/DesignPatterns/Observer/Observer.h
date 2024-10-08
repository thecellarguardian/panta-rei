/**
 * @file Observer.h
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

class Subject;

#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * @class Observer
 * @brief This class models a state observer.
 * An Observer object has to be registered to a Subject object in order to be
 * notified when its state changes, and act properly.
 * @see Observer Design Pattern.
 **/
class Observer
{
    public:
        virtual ~Observer(){}
        /**
         * This method is called by the Subject to the which this Observer is
         * registered. The specific actions to be done can be defined through
         * polimorphism.
         **/
        virtual void update(Subject*) = 0;
};

#endif
