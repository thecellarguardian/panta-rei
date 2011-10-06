#include "../src/Model/Activator/Activator.h"
#include "../src/Model/Scheduler/DeadlineMonotonic/DeadlineMonotonic.h"
#include "../src/Model/SystemQueuesManager/SystemQueuesManager.h"
#include "../src/Model/Task/PeriodicTask/PeriodicTask.h"
#include <boost/shared_ptr.hpp>

int main()
{
	Timer timer(1, 28);
	boost::shared_ptr<SystemQueuesManager> systemQueues(new SystemQueuesManager());
	boost::shared_ptr<Activator> activator(new Activator(systemQueues, &timer));
	boost::shared_ptr<Scheduler> scheduler(new DeadlineMonotonic(false, systemQueues, &timer, activator));
	boost::shared_ptr<Task> p1(new PeriodicTask(1, 0, 4, 5, 6, &timer));
	boost::shared_ptr<Task> p2(new PeriodicTask(2, 3, 2, 4, 4, &timer));
	boost::shared_ptr<Task> p3(new PeriodicTask(3, 4, 5, 7, 8, &timer));
	activator->registerForActivation(p1);
	activator->registerForActivation(p2);
	activator->registerForActivation(p3);
	timer.start();
	return 0;
}


