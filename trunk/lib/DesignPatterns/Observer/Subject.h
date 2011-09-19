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
 *
 */

#include "Observer.h"
#include <list>
#include <boost/shared_ptr.hpp>

#ifndef SUBJECT_H
#define SUBJECT_H

/**
 * @class Subject
 *
 * @brief This class models a subject of observation.
 * @see "Observer design pattern."
 * Un oggetto di tipo Subject consente ad oggetti di tipo Observer di
 * registrarsi al fine di ricevere notifiche quando un cambiamento di stato
 * significativo occorre.
 *
 */
 
class Subject
{
    private:
        /**
         * Lista degli Observer registrati, gli Observer che desiderano ricevere
         * notifiche quando lo stato del Subject cambia.
         */
        std::list< boost::shared_ptr<Observer> > attachedObservers;
    public:
        /**
         * Questo metodo consente di registrare un Observer.
         */
        void attach(boost::shared_ptr<Observer> observerToAttach);
        /**
         * Questo metodo consente di deregistrare un Observer.
         */
        void detach(boost::shared_ptr<Observer> observerToDetach)
        /**
         * Questo metodo consente di notificare a tutti gli Observer registrati
         * su questo Subject che il suo stato è cambiato.
         */
        void notify();
};

#endif
