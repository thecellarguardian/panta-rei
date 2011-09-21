#include "../lib/DesignPatterns/Observer/Observer.h"
#include "../src/Model/Timer/Timer.h"
#include "../src/Model/Task/PeriodicTask/PeriodicTask.h"
#include <iostream>
#include <string>

int main()
{
	boost::shared_ptr<Timer> pt(new Timer(1, 13));
	boost::shared_ptr<PeriodicTask> p1(new PeriodicTask(1, 0, 4, 5, 6, pt.get()));
	boost::shared_ptr<PeriodicTask> p2(new PeriodicTask(2, 3, 2, 4, 4, pt.get()));
	boost::shared_ptr<PeriodicTask> p3(new PeriodicTask(3, 4, 5, 7, 8, pt.get()));
	pt->start();
	return 0;
}
