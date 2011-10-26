#include <typeinfo>
#include <iostream>
#include "Subject.h"
#ifndef OBSERVER_HHHH
#define OBSERVER_HHHH

class Observer
{
    public:
            void update(Subject* subject);
            };
#endif
