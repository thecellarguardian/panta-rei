#include "../src/Model/Activator/Activator.h"
#include "../src/Model/Scheduler/EarliestDeadlineFirst/EarliestDeadlineFirst.h"
#include "../src/Model/Scheduler/DeadlineMonotonic/DeadlineMonotonic.h"
#include "../src/Model/SystemQueuesManager/SystemQueuesManager.h"
#include "../src/Model/Task/PeriodicTask/PeriodicTask.h"
#include "../src/Model/History/History.h"
#include "../src/Model/SchedulationEvents/SchedulingEventVisitor.h"
#include "../lib/EventManagement/Event/Event.h"
#include "../lib/gnuplot-cpp/gnuplot_i.hpp"
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
};

class GnuplotSchedulingEventVisitor : public SchedulingEventVisitor
{
    private:
        Gnuplot plotter;
        std::map< unsigned int, std::vector<unsigned int> > arrivalInstants;
        std::map< unsigned int, std::vector<unsigned int> >
            pendingArrivalInstants;
        std::map< unsigned int, std::vector<unsigned int> >
            deadlineMissInstants;
        std::vector<unsigned int> endOfComputationInstants;
        std::vector<unsigned int> scheduleInstants;
        std::vector<unsigned int> preemptionOriginInstants;
        std::vector<unsigned int> preemptionDestinationInstants;
    public:
    GnuplotSchedulingEventVisitor() : plotter("lines"){}
    void visit(VisitableSchedulingEvent<ARRIVAL>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        while(arrivalInstants[subject].size() < instant + 1)
        {
            arrivalInstants[subject].push_back(0);
        }
        arrivalInstants[subject][instant] = subject;
    }
    void visit(VisitableSchedulingEvent<PENDING_ARRIVAL>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        while(pendingArrivalInstants[subject].size() < instant + 1)
        {
            pendingArrivalInstants[subject].push_back(0);
        }
        pendingArrivalInstants[subject][instant] = subject;
    }
    void visit(VisitableSchedulingEvent<DEADLINE_MISS>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        while(deadlineMissInstants[subject].size() < instant + 1)
        {
            deadlineMissInstants[subject].push_back(0);
        }
        deadlineMissInstants[subject][instant] = subject;
    }
    void visit(VisitableSchedulingEvent<END_OF_COMPUTATION>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        while(endOfComputationInstants.size() < instant + 1)
        {
            endOfComputationInstants.push_back(0);
        }
        endOfComputationInstants[instant] = subject;
    }
    void visit(VisitableSchedulingEvent<SCHEDULE>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        while(scheduleInstants.size() < instant + 1)
        {
            scheduleInstants.push_back(0);
        }
        scheduleInstants[instant] = subject;
    }
    void visit(VisitableSchedulingEvent<PREEMPTION_ORIGIN>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        while(preemptionOriginInstants.size() < instant + 1)
        {
            preemptionOriginInstants.push_back(0);
        }
        preemptionOriginInstants[instant] = subject;
    }
    void visit(VisitableSchedulingEvent<PREEMPTION_DESTINATION>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        while(preemptionDestinationInstants.size() < instant + 1)
        {
            preemptionDestinationInstants.push_back(0);
        }
        preemptionDestinationInstants[instant] = subject;
    }
    void plot()
    {
        plotter.reset_plot();
        /*plotter.set_style("points");
        for(
                std::map< unsigned int, std::vector<unsigned int> >::iterator i = arrivalInstants.begin();
                i != arrivalInstants.end();
                i++
            )
        {
            plotter.plot_x((*i).second, "Arrival time for task i");
        }
        for(
                std::map< unsigned int, std::vector<unsigned int> >::iterator i = pendingArrivalInstants.begin();
                i != pendingArrivalInstants.end();
                i++
            )
        {
            plotter.plot_x((*i).second, "Pending arrival time for task i");
        }
        for(
                std::map< unsigned int, std::vector<unsigned int> >::iterator i = deadlineMissInstants.begin();
                i != deadlineMissInstants.end();
                i++
            )
        {
            plotter.plot_x((*i).second, "Deadline miss for task i");
        }
        //plotter.plot_x(endOfComputationInstants, "End of computation");
        plotter.plot_x(preemptionOriginInstants, "Preemption origin");
        plotter.plot_x(preemptionDestinationInstants, "Preemption origin");*/
        plotter.set_style("steps");
        plotter.plot_x(schedule, "Schedule");
        char a = 'a';
        std::cin >> a;
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
	SchedulingEventVisitor* visitor = new GnuplotSchedulingEventVisitor;
	//SchedulingEventVisitor* visitor = new TestVisitor;
	history.accept(visitor);
	(dynamic_cast<GnuplotSchedulingEventVisitor*>(visitor))->plot();
	delete visitor;
	return 0;
}


