/**
 * @file Register.h
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

#include <boost/shared_ptr.hpp>
#include <map>
using namespace std;
using namespace boost;

#ifndef REGISTER_H
#define REGISTER_H

template <typename Key, typename Value> class Register
{
    private:
        map< Key, shared_ptr<Value> > dataStructure;
    protected:
    public:
        void addElement(shared_ptr<Value> elementPointer)
        {
            dataStructure[elementPointer->getID()] = elementPointer;
        }
        void eraseElement(Key key)
        {
            dataStructure.erase(key);
        }
        shared_ptr<Value> operator[](Key key)
        {
            return dataStructure[key];
        }
};

#endif
