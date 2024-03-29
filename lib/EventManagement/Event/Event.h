/**
 * @file Event.h
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

#include <iostream>

#ifndef SIMPLE_EVENT_H
#define SIMPLE_EVENT_H

/**
 * @class Event
 * @brief Event interface.
 * An event is a vector of three informations: an instant, a subject and an
 * action. This interface stores the subject and instant information, while the
 * action is held by the particular type inheriting this interface (as an
 * example, think at a WinEvent inheriting this interface, the type is the
 * vector for the action information).
 * The first template parameter is the type of the subject identifier, while the
 * second is a (numerical, usually) type to navigate the time dimension.
 **/
template <typename SubjectIdentifier, typename Time> class Event
{
    private:
        const SubjectIdentifier subject;
        const Time instant;
    public:
        Event(SubjectIdentifier subjectToSet, Time instantToSet)
            : subject(subjectToSet), instant(instantToSet){}
        virtual ~Event(){}
        /** This method returns the subject information. */
        SubjectIdentifier getSubject(){return subject;}
        /** This method returns the temporal information. */
        Time getInstant(){return instant;}
};

#endif
