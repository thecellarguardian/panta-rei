#include "../src/Model/SchedulingSimulation/SchedulingSimulation.h"
#include "../src/View/GnuplotSchedulingEventVisitor/GnuplotSchedulingEventVisitor.h"
#include "../src/Model/Scheduler/EarliestDeadlineFirst/EarliestDeadlineFirst.h"

int main()
{
	SchedulingSimulation simulation;
	GnuplotSchedulingEventVisitor visitor;
	simulation.setSimulationLength(35);
	simulation.setSchedulingAlgorithm<EarliestDeadlineFirst>(true);
	simulation.createPeriodicTask(0, 2, 5, 5);
	simulation.createPeriodicTask(0, 4, 7, 7);
	simulation.simulate();
	simulation.accept(&visitor);
	visitor.plot();
	char a = 'a';
	std::cin >> a;
	return 0;
}
