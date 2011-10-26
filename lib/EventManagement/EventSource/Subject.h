#include <typeinfo>
#include <iostream>
#ifndef SUBJECT_HHHH
#define SUBJECT_HHHH

class Observer;

class Subject
{
    public:
            virtual void notify(Observer* observer);
            };

#endif

