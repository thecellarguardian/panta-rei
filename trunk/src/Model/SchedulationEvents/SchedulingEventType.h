/**
 * @file SchedulingEventType.h
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

#ifndef SCHEDULING_EVENT_TYPE_H
#define SCHEDULING_EVENT_TYPE_H

/**
 * @enum SchedulingEventType
 * @brief Scheduling event types.
 * This enum refers, with its value set, the possible schedulation events. These
 * events are fixed, so the value set of this enum is supposed not to change
 * frequently or at all. This enum is useful if used as a parameter of the
 * VisitableSchedulingEvent class, which is template-parametric in
 * SchedulingEventType.
 * @see VisitableSchedulingEvent
 **/
enum SchedulingEventType
{
    ARRIVAL,
    END_OF_COMPUTATION,
    DEADLINE_MISS,
    SCHEDULATION,
    PREEMPTION //TODO complete the list
};

#endif
