#include "../src/Model/Activator/Activator.h"
#include "../src/Model/Scheduler/EarliestDeadlineFirst/EarliestDeadlineFirst.h"
#include "../src/Model/Scheduler/DeadlineMonotonic/DeadlineMonotonic.h"
#include "../src/Model/SystemQueuesManager/SystemQueuesManager.h"
#include "../src/Model/Task/PeriodicTask/PeriodicTask.h"
#include "../src/Model/History/History.h"
#include "../src/Model/SchedulationEvents/SchedulingEventVisitor.h"
#include "../lib/EventManagement/Event/Event.h"
#include <boost/shared_ptr.hpp>

class TestVisitor : public SchedulingEventVisitor
{
	public:
	void visit(VisitableSchedulingEvent<ARRIVAL>* event)
	{
		std::cout << "VISITOR: ARRIVAL EVENT VISITED" <<
		             "<" << event->getSubject() << ", " <<
		             event->getInstant() << ">" << std::endl;
	}
	void visit(VisitableSchedulingEvent<PENDING_ARRIVAL>* event)
	{
		std::cout << "VISITOR: PENDING_ARRIVAL EVENT VISITED" <<
		             "<" << event->getSubject() << ", " <<
		             event->getInstant() << ">" << std::endl;
	}
	void visit(VisitableSchedulingEvent<END_OF_COMPUTATION>* event)
	{
		std::cout << "VISITOR: END_OF_COMPUTATION EVENT VISITED" <<
		             "<" << event->getSubject() << ", " <<
		             event->getInstant() << ">" << std::endl;
	}
	void visit(VisitableSchedulingEvent<DEADLINE_MISS>* event)
	{
		std::cout << "VISITOR: DEADLINE_MISS EVENT VISITED" <<
		             "<" << event->getSubject() << ", " <<
		             event->getInstant() << ">" << std::endl;

	}
	void visit(VisitableSchedulingEvent<SCHEDULE>* event)
	{
		std::cout << "VISITOR: SCHEDULE EVENT VISITED" <<
		             "<" << event->getSubject() << ", " <<
		             event->getInstant() << ">" << std::endl;
	}
	void visit(VisitableSchedulingEvent<PREEMPTION_ORIGIN>* event)
	{
		std::cout << "VISITOR: PREEMPTION_ORIGIN EVENT VISITED" <<
		             "<" << event->getSubject() << ", " <<
		             event->getInstant() << ">" << std::endl;
	}
	void visit(VisitableSchedulingEvent<PREEMPTION_DESTINATION>* event)
	{
		std::cout << "VISITOR: PREEMPTION_DESTINATION EVENT VISITED" <<
		             "<" << event->getSubject() << ", " <<
		             event->getInstant() << ">" << std::endl;
	}
	void visit(VisitableSchedulingEvent<IDLE>* event)
	{
		std::cout << "VISITOR: IDLE EVENT VISITED" <<
		             "<" << event->getSubject() << ", " <<
		             event->getInstant() << ">" << std::endl;
	}
};

int main()
{
	Timer timer(1, 100);
	boost::shared_ptr<SystemQueuesManager> systemQueues(new SystemQueuesManager());
	boost::shared_ptr<Activator> activator(new Activator(systemQueues, &timer));
	boost::shared_ptr<Scheduler> scheduler(new DeadlineMonotonic(true, systemQueues, &timer, activator));
	boost::shared_ptr<Task> p1(new PeriodicTask(1, 0, 2, 5, 5, &timer));
	boost::shared_ptr<Task> p2(new PeriodicTask(2, 0, 4, 7, 7, &timer));
	History< Event<unsigned int, unsigned int> > history;
	history.registerToEventSource(activator.get());
	history.registerToEventSource(scheduler.get());
	history.registerToEventSource(p1.get());
	history.registerToEventSource(p2.get());
	activator->registerForActivation(p1);
	activator->registerForActivation(p2);
	timer.start();
	SchedulingEventVisitor* visitor = new TestVisitor;
	history.accept(visitor);
	delete visitor;
	return 0;
}


