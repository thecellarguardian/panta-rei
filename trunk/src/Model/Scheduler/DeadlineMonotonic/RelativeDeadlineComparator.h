/**
 * @file RelativeDeadlineComparator.h
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

#include <boost/shared_ptr.hpp>
#include "../../Task/Task.h"

#ifndef RELATIVE_DEADLINE_COMPARATOR_H
#define RELATIVE_DEADLINE_COMPARATOR_H

/**
 * @class RelativeDeadlineComparator
 * @brief Priority function based on periods.
 * As each priority comparator, PeriodComparator is a functor which takes two
 * Task and returns true if the priority of the first is greater than the one
 * of the second. The priority law in this case is inversely proportional to
 * the Task relative deadline.
 **/
class RelativeDeadlineComparator
{
    public:
        bool operator()(boost::shared_ptr<Task> a, boost::shared_ptr<Task> b)
        {
            return (a->getRelativeDeadline() < b->getRelativeDeadline());
        }
};

#endif
