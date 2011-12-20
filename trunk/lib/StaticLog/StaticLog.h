/**
 * @file StaticLog.h
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

#include <map>
#include <iostream>

#ifndef STATIC_LOG_H
#define STATIC_LOG_H

/**
 * @namespace StaticLog
 * @brief A simple logger.
 * StaticLog maintains a static map of loggers. Each StaticLog client has to be
 * sure that the used logger has been properly initialized.
 **/

class StaticLog
{
    public:
        static std::map<std::string, std::ostream*> log;
};

#endif
