#include "Subject.h"
#include "EventSource.h"

#ifndef EVSOURCESUB
#define EVSOURCESUB
class EventSourceSubject : public Subject, public EventSource {};
#endif
