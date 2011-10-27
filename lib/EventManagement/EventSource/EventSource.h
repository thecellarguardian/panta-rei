/**
 * @file EventSource.h
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

 /**
 * @class EventSource
 * @brief A generic source of events.
 * This class models a generic source of events.
 * It is a QueueInterface and a Subject, and it's template parametric in a
 * ParticularQueueImplementation, so that every event can be stored in a proper
 * data structure. An event source can produce and store events in it's queue,
 * and, when the right time arrives, a call to the inherited notify() method
 * will let every Observer know that events have been produced, so that they can
 * get them through the getEventList() method.
 * @see Subject, Event
 **/
