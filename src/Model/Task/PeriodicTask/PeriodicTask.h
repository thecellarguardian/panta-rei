/**
 * @file PeriodicTask.h
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

#include "../Task.h"

class PeriodicTask : public Task
{
    private:
        const int period;
        int currentInstanceArrivalTime;
        int remainingPeriod;
    protected:
    public:
        PeriodicTask
        (
            const int taskID,
            const int arrivalTime,
            const int computationTime,
            const int relativeDeadline,
            const int period
        )
    int getCurrentInstanceArrivalTime();
    int getRemainingPeriod();
    virtual void update();
    void reset();
}
