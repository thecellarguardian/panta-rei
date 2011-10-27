/**
 * @file Subject.h
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

#include "Observer.h"
#include <list>
#include <boost/shared_ptr.hpp>

#ifndef SUBJECT_H
#define SUBJECT_H

/**
 * @class Subject
 * @brief This class models a subject of observation.
 * A Subject object lets Observer object to register themselves, in order to
 * be notified when the Subject's state changes.
 * @see "Observer design pattern."
 **/
class Subject
{
    private:
        std::list<Observer*> attachedObservers;
        /**<
         * Registered Observers list. These object have to be notified when the
         * Subject' s state changes. Notice the use of simple pointer instead of
         * a shared_ptr: the Subject is a subject of observation, thus it
         * doesn't make any sense, for a Subject, to have lifecycle control over
         * its observers.
         **/
    public:
        virtual ~Subject();
        /**
         * You can register an Observer using this method.
         * @param observerToAttach Observer object to register.
         **/
        virtual void attach(Observer* observerToAttach);
        /**
         * You can de-register an Observer using this method.
         * @param observerToDetach Observer object to de-register.
         **/
        virtual void detach(Observer* observerToDetach);
        /**
         * Each registered Observer is notified about the new state of
         * the Subject.
         **/
        virtual void notify();
};

#endif
