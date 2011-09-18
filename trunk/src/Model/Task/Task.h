/**
 * @file Task.h
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

enum TaskState
{
    NEW,
    READY,
    EXECUTING,
    SUSPENDED
};

class Task
{
    private:
        const int taskID;
        const int arrivalTime;
        const int computationTime;
        const int relativeDeadline;
        int absoluteDeadline;
        int elapsedTime;
        int remainingComputationTime;
        int instantaneousExceedingTime;
        TaskState currentState;
    protected:
    public:
    Task
    (
        const int taskID,
        const int arrivalTime,
        const int computationTime,
        const int relativeDeadline
    );
    int getTaskID();
    int getArrivalTime();
    int getComputationTime();
    int getRelativeDeadline();
    int getAbsoluteDeadline();
    int getElapsedTime();
    int getInstantaneousExceedingTime();
    bool deadlineMiss();
    void setState(TaskState stateToSet);
    TaskState getState();
    virtual void update() = 0;
};
