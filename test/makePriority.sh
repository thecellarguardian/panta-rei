g++ \
../src/Model/Activator/*.cpp \
../src/Model/Scheduler/*.cpp \
../src/Model/SystemQueuesManager/SystemQueuesManager.cpp \
../src/Model/Task/*.cpp \
../src/Model/Task/PeriodicTask/*.cpp \
../src/Model/Timer/Timer.cpp \
../lib/DesignPatterns/Observer/Subject.cpp \
provaPriorityScheduler.cpp \
-lboost_thread -lpthread -g -p -Wall -pedantic-errors