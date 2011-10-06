g++ \
provaScheduling.cpp \
../src/Model/Activator/*.cpp \
../src/Model/Scheduler/*.cpp \
../src/Model/Scheduler/DeadlineMonotonic/*.cpp \
../src/Model/SystemQueuesManager/SystemQueuesManager.cpp \
../src/Model/Task/*.cpp \
../src/Model/Task/PeriodicTask/*.cpp \
../src/Model/Timer/Timer.cpp \
../lib/DesignPatterns/Observer/Subject.cpp \
-lboost_thread -lpthread -pg -Wall
