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
#include <boost/lexical_cast.hpp>
#include <string>

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
            deadlineMissInstants;
        std::vector<unsigned int> endOfComputationInstants;
        std::vector<unsigned int> endingTasks;
        std::vector<unsigned int> scheduleInstants;
        std::vector<unsigned int> scheduledTasks;
        std::vector<unsigned int> preemptionOriginInstants;
        std::vector<unsigned int> preemptingOutTasks;
        std::vector<unsigned int> preemptionDestinationInstants;
        std::vector<unsigned int> preemptingInTasks;
        unsigned int lowestTaskID;
        unsigned int highestTaskID;
        void updateTaskIDRange(unsigned int subject)
        {
            if(subject > highestTaskID)
            {
                highestTaskID = subject;
                return;
            }
        }
    public:
    GnuplotSchedulingEventVisitor() : plotter("steps")
    {
    	plotter.set_ylabel("Time");
    	plotter.set_xlabel("Tasks");
        plotter.cmd("set xtics 1");
        plotter.cmd("set ytics 1,1");
        plotter.set_grid();
    	lowestTaskID = 1;
    	highestTaskID = 1;
    }
    void visit(VisitableSchedulingEvent<ARRIVAL>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        arrivalInstants[subject].push_back(instant);
        updateTaskIDRange(subject);
    }
    void visit(VisitableSchedulingEvent<PENDING_ARRIVAL>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        arrivalInstants[subject].push_back(instant);
        updateTaskIDRange(subject);
    }
    void visit(VisitableSchedulingEvent<DEADLINE_MISS>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        deadlineMissInstants[subject].push_back(instant);
        updateTaskIDRange(subject);
    }
    void visit(VisitableSchedulingEvent<END_OF_COMPUTATION>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        endOfComputationInstants.push_back(instant);
        endingTasks.push_back(subject);
        updateTaskIDRange(subject);
    }
    void visit(VisitableSchedulingEvent<SCHEDULE>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        if(subject != 0)
        {
            scheduleInstants.push_back(instant);
            scheduledTasks.push_back(subject);
            updateTaskIDRange(subject);
        }
    }
    void visit(VisitableSchedulingEvent<PREEMPTION_ORIGIN>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        preemptionOriginInstants.push_back(instant);
        preemptingOutTasks.push_back(subject);
        updateTaskIDRange(subject);
    }
    void visit(VisitableSchedulingEvent<PREEMPTION_DESTINATION>* event)
    {
        unsigned int subject = event->getSubject();
        unsigned int instant = event->getInstant();
        preemptionDestinationInstants.push_back(instant);
        preemptingInTasks.push_back(subject);
        updateTaskIDRange(subject);
    }
    void plot()
    {
        plotter.set_style("points");
        std::cout << "lowest: " << lowestTaskID << ", highest: " << highestTaskID << std::endl;
        plotter.set_yrange(lowestTaskID, 2*highestTaskID);
        for
            (
                std::map< unsigned int, std::vector<unsigned int> >::iterator i = arrivalInstants.begin();
                i != arrivalInstants.end();
                i++
            )
        {
            std::string legend("Arrival time for task ");
            legend.append(boost::lexical_cast<std::string>((*i).first));
            std::vector<unsigned int> task((*i).second.size(), (*i).first);
            plotter.plot_xy((*i).second, task, legend);
        }
        for
            (
                std::map< unsigned int, std::vector<unsigned int> >::iterator i = deadlineMissInstants.begin();
                i != deadlineMissInstants.end();
                i++
            )
        {
            std::string legend("Deadline miss for task ");
            legend.append(boost::lexical_cast<std::string>((*i).first));
            std::vector<unsigned int> task((*i).second.size(), (*i).first);
            plotter.plot_xy((*i).second, task, legend);
        }
        plotter.plot_xy(endOfComputationInstants, endingTasks, "End of computation");
        plotter.plot_xy(preemptionOriginInstants, preemptingOutTasks, "Preemption origin");
        plotter.plot_xy(preemptionDestinationInstants, preemptingInTasks, "Preemption origin");
        plotter.set_style("steps");
        plotter.plot_xy(scheduleInstants, scheduledTasks, "Schedule");
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


