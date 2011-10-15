#include "../src/Model/Timer/Timer.h"
#include "../src/Model/Task/Task.h"
#include "../src/Model/Task/PeriodicTask/PeriodicTask.h"
#include <boost/shared_ptr.hpp>

int main()
{
	Timer timer;
	boost::shared_ptr<Task> p1(new PeriodicTask(1, 0, 4, 5, 6, &timer));
	p1->setState(EXECUTING);
	timer.start();
	return 0;
}
