/**
 * @file DeadlineMonotonic.h
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

#include "../PriorityScheduler/PriorityScheduler.h"
#include "RelativeDeadlineComparator.h"

#ifndef DEADLINE_MONOTONIC_H
#define DEADLINE_MONOTONIC_H

typedef PriorityScheduler<RelativeDeadlineComparator> DeadlineMonotonic;

#endif
