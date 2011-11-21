#include "../src/Model/SchedulingSimulation/SchedulingSimulation.h"
#include "../src/View/GnuplotSchedulingEventVisitor/GnuplotSchedulingEventVisitor.h"
#include "../src/Model/Scheduler/EarliestDeadlineFirst/EarliestDeadlineFirst.h"

int main()
{
	SchedulingSimulation simulation;
	GnuplotSchedulingEventVisitor visitor;
	simulation.setSimulationLength(100);
	simulation.setSchedulingAlgorithm<EarliestDeadlineFirst>(true);
	simulation.createPeriodicTask(0, 2, 5, 6);
	simulation.createPeriodicTask(0, 2, 4, 8);
	simulation.createPeriodicTask(0, 4, 8, 12);
	simulation.createPeriodicTask(13, 7, 8, 10);
	simulation.simulate();
	simulation.accept(&visitor);
	visitor.plot();
	return 0;
}
