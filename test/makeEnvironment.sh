g++ \
../src/Model/Activator/*.cpp \
../src/Model/Scheduler/*.cpp \
../src/Model/SystemQueuesManager/SystemQueuesManager.cpp \
../src/Model/Task/*.cpp \
../src/Model/Task/PeriodicTask/*.cpp \
../src/Model/Timer/Timer.cpp \
../src/Model/SchedulingSimulation/SchedulingSimulation.cpp \
../lib/DesignPatterns/Observer/Subject.cpp \
provaEnvironment.cpp \
-lboost_thread -lpthread -g -p
