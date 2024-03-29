g++ \
Model/Activator/*.cpp \
Model/Scheduler/*.cpp \
Model/SystemQueuesManager/SystemQueuesManager.cpp \
Model/Task/*.cpp \
Model/Task/PeriodicTask/*.cpp \
Model/Timer/Timer.cpp \
Model/SchedulingSimulation/SchedulingSimulation.cpp \
../lib/DesignPatterns/Observer/Subject.cpp \
../lib/StaticLog/StaticLog.cpp \
PantaRei.cpp \
-o ../bin/panta-rei \
-lboost_system -lboost_thread -lboost_program_options -lpthread -g -p
