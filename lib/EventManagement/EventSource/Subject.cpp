#include "Subject.h"
#include "Observer.h"
void Subject::notify(Observer* observer)
                    {
                                                    std::cout << typeid(this).name() << std::endl;
                                                                                                observer->update(this);
                                                                                                                                                    }
