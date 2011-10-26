#include <iostream>
#include <typeinfo>
#include "Observer.h"
#include "Subject.h"
#include "EventSourceSubject.h"

int main()
{
	EventSourceSubject ess;
	Observer o;
	ess.notify(&o);
	Subject s;
	s.notify(&o);
	return 0;
}
