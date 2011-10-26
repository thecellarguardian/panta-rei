#include "Observer.h" 
#include "EventSource.h" 
#include "EventSourceSubject.h" 
#include "Subject.h" 
#include <cassert>
void Observer::update(Subject* subject) 
{ 
	std::cout << typeid(subject).name() << std::endl;
//	EventSourceSubject* ess = dynamic_cast<EventSourceSubject*>(subject);
//	std::cout << typeid(ess).name() << std::endl; 
	EventSource* evs = dynamic_cast<EventSource*>(subject); 
	assert(evs != NULL);
	std::cout << typeid(evs).name() << std::endl; 
	evs->print(); 
}
