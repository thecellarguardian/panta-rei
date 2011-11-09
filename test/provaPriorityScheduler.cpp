#include "../src/Model/Activator/Activator.h"
#include "../src/Model/Scheduler/EarliestDeadlineFirst/EarliestDeadlineFirst.h"
#include "../src/Model/Scheduler/DeadlineMonotonic/DeadlineMonotonic.h"
#include "../src/Model/SystemQueuesManager/SystemQueuesManager.h"
#include "../src/Model/Task/PeriodicTask/PeriodicTask.h"
#include "../src/Model/History/History.h"
#include "../src/Model/SchedulationEvents/SchedulingEventVisitor.h"
#include "../src/View/GnuplotSchedulingEventVisitor/GnuplotSchedulingEventVisitor.h"
#include "../lib/EventManagement/Event/Event.h"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

int main()
{
	Timer timer(1, 100);
	boost::shared_ptr<SystemQueuesManager> systemQueues(new SystemQueuesManager());
	boost::shared_ptr<Activator> activator(new Activator(systemQueues, &timer));
	boost::shared_ptr<Scheduler> scheduler(new DeadlineMonotonic(true, systemQueues, &timer, activator));
	//boost::shared_ptr<Task> p1(new PeriodicTask(1, 0, 2, 5, 5, &timer));
	//boost::shared_ptr<Task> p2(new PeriodicTask(2, 0, 4, 7, 7, &timer));
	boost::shared_ptr<Task> p1(new PeriodicTask(1, 0, 2, 5, 6, &timer));
	boost::shared_ptr<Task> p2(new PeriodicTask(2, 0, 2, 4, 8, &timer));
	boost::shared_ptr<Task> p3(new PeriodicTask(3, 0, 4, 8, 12, &timer));
	History< Event<unsigned int, unsigned int> > history;
	history.registerToEventSource(activator.get());
	history.registerToEventSource(scheduler.get());
	history.registerToEventSource(p1.get());
	history.registerToEventSource(p2.get());
	history.registerToEventSource(p3.get());
	activator->registerForActivation(p1);
	activator->registerForActivation(p2);
	activator->registerForActivation(p3);
	timer.start();
	SchedulingEventVisitor* visitor = new GnuplotSchedulingEventVisitor;
	//SchedulingEventVisitor* visitor = new TestVisitor;
	history.accept(visitor);
	(dynamic_cast<GnuplotSchedulingEventVisitor*>(visitor))->plot();
	delete visitor;
	return 0;
}


