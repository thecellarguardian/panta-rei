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
 * example, think at a WinEvent inheriting this interface, the type is a vector
 * for the action information).
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
        SubjectIdentifier getSubject(){return subject;}
        Time getInstant(){return instant;}
        void print()
        {
            std::cout << "event<SubjectID: " << subject << ", instant: "
                << instant << ")" << std::endl;
        }
};

#endif
