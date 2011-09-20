#include "../lib/DesignPatterns/Observer/Observer.h"
#include "../src/Model/Timer/Timer.h"
#include <iostream>
#include <string>

class TimerObserver : public Observer
{
	boost::shared_ptr<Timer> timer;
	std::string name;
	public:
	TimerObserver(boost::shared_ptr<Timer> timerToSet, std::string nameToSet)
		: timer(timerToSet), name(nameToSet)
		{}
		void update()
		{
			std::cout << name << ": OK, time: " << timer->getCurrentTime() << std::endl;
		}
}

int main()
{
	Timer t(1, 100);
}
