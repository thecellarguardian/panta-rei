/**
 * @file Subject.cpp
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

#include "Subject.h"
#include <iostream>

Subject::~Subject(){}

void Subject::attach(Observer* observerToAttach)
{
    attachedObservers.push_back(observerToAttach);
}

void Subject::detach(Observer* observerToDetach)
{
    attachedObservers.remove(observerToDetach);
    //Notice that this operation will remove the pointer, not the object!
}

void Subject::detachAll()
{
    attachedObservers.erase(attachedObservers.begin(), attachedObservers.end());
    //Notice that this operation will remove the pointers, not the objects!
}

void Subject::substitute(Observer* observerToSubstitute, Observer* substitute)
{
    for
        (
            std::list<Observer*>::iterator i = attachedObservers.begin();
            i != attachedObservers.end();
            i++
        )
    {
        if((*i) == observerToSubstitute)
        {
            (*i) = substitute;
            break;
        }
    }
}

void Subject::notify()
{
    std::list<Observer*>::iterator i = attachedObservers.begin();
    for(; i != attachedObservers.end(); i++)
    {
        (*i)->update(this);
    }
}
