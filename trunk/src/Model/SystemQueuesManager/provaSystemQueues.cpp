#include "SystemQueuesManager.h"
#include "../Task/PeriodicTask/PeriodicTask.h"
#include "../Activator/Activator.h"
#include "../Timer/Timer.h"
#include "../../../lib/Queue/QueueImplementation/QueueImplementation.h"
#include "../../../lib/Queue/QueueImplementationProvider/QueueImplementationProvider.h"
#include "../../../lib/Queue/Implementations/OrderedQueueImplementation/OrderedQueueImplementation.h"
#include <boost/shared_ptr.hpp>
#include <iostream>

/*class TaskArrivalComparator
{
    public:
    	bool operator()(boost::shared_ptr<Task>& a, boost::shared_ptr<Task>& b)
        {
        	return (a->getCurrentInstanceArrivalTime() < b->getCurrentInstanceArrivalTime());
        }
};

class Activator : public QueueImplementationProvider<Task>
{
	private:
		boost::shared_ptr<SystemQueuesManager> systemQueues;
		boost::shared_ptr< QueueInterface<Task> > activationQueue;
	public:
		Activator(boost::shared_ptr<SystemQueuesManager> systemQueuesToSet) : systemQueues(systemQueuesToSet)
		{
			activationQueue = (*systemQueues)["activation"];
			activationQueue->setImplementation(getImplementation());
		}
		boost::shared_ptr< QueueImplementation<Task> > getImplementation()
		{
			boost::shared_ptr< QueueImplementation<Task> > implementationToReturn
				(
			    	new OrderedQueueImplementation<Task, TaskArrivalComparator>()
		    	);
		    return implementationToReturn;
		}
		void registerForActivation(boost::shared_ptr<Task> taskToRegister)
		{
			activationQueue->insert(taskToRegister);
		}
		void print()
		{
			activationQueue->print();
		}
};*/

int main()
{
	Timer timer(1, 100);
	boost::shared_ptr<SystemQueuesManager> systemQueues(new SystemQueuesManager());
	Activator activator(systemQueues, &timer);
	boost::shared_ptr<Task> p0(new PeriodicTask(0, 0, 3, 4, 6, &timer));
	boost::shared_ptr<Task> p1(new PeriodicTask(1, 2, 2, 3, 4, &timer));
	boost::shared_ptr<Task> p2(new PeriodicTask(2, 3, 4, 4, 6, &timer));
	boost::shared_ptr<Task> p3(new PeriodicTask(3, 3, 4, 5, 7, &timer));
	boost::shared_ptr<Task> p4(new PeriodicTask(4, 2, 3, 4, 6, &timer));
	boost::shared_ptr<Task> p5(new PeriodicTask(5, 5, 3, 4, 6, &timer));
	activator.registerForActivation(p0);
	activator.registerForActivation(p1);
	activator.registerForActivation(p2);
	activator.registerForActivation(p3);
	activator.registerForActivation(p4);
	activator.registerForActivation(p5);
	activator.print();
	timer.start();
	return 0;
}
