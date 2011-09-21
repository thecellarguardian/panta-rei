#include "../lib/DesignPatterns/Observer/Observer.h"
#include "../src/Model/Timer/Timer.h"
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include <string>

class TimerObserver
: public Observer, public boost::enable_shared_from_this<TimerObserver>
{
		Timer* timer;
		std::string name;
	public:
		TimerObserver(Timer* timerToSet, std::string nameToSet)
			: timer(timerToSet), name(nameToSet)
			{
				timer->attach(this);
			}
		void update()
		{
			std::cout << name << ": OK, time: " << timer->getCurrentTime() << std::endl;
		}
};

int main()
{
	boost::shared_ptr<Timer> pt(new Timer(1, 100));
	boost::shared_ptr<TimerObserver> p1(new TimerObserver(pt.get(), "primo"));
	boost::shared_ptr<TimerObserver> p2(new TimerObserver(pt.get(), "secondo"));
	boost::shared_ptr<TimerObserver> p3(new TimerObserver(pt.get(), "terzo"));
	boost::shared_ptr<TimerObserver> p4(new TimerObserver(pt.get(), "quarto"));
	boost::shared_ptr<TimerObserver> p5(new TimerObserver(pt.get(), "quinto"));
	pt->start();
	return 0;
}
