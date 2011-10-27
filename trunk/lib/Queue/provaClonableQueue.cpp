#include "QueueInterface/QueueInterface.h"
#include "QueueImplementation/QueueImplementation.h"
#include "Implementations/OrderedQueueImplementation/OrderedQueueImplementation.h"
#include "Implementations/SingleSlotQueueImplementation/SingleSlotQueueImplementation.h"
#include <boost/shared_ptr.hpp>
#include <iostream>

class IntComparator
{
    public:
    	bool operator()(boost::shared_ptr<int> a, boost::shared_ptr<int> b)
    	{
        	return ((*a) < (*b));
        }
};

int main()
{
	QueueInterface<int> qI;
	boost::shared_ptr< QueueImplementation<int> > impPtr;
	{
			boost::shared_ptr< QueueImplementation<int> > innerPtr(new OrderedQueueImplementation<int, IntComparator>);
			qI.attachImplementation(innerPtr);
			boost::shared_ptr<int> p1(new int(10));
			boost::shared_ptr<int> p2(new int(1));
			boost::shared_ptr<int> p3(new int(12));
			boost::shared_ptr<int> p4(new int(4));
			boost::shared_ptr<int> p5(new int(42));
			boost::shared_ptr<int> p6(new int(17));
			boost::shared_ptr<int> p7(new int(3));
			boost::shared_ptr<int> p8(new int(2));
			qI.insert(p1);
			qI.insert(p2);
			qI.insert(p3);
			qI.insert(p4);
			qI.insert(p5);
			qI.insert(p6);
			qI.insert(p7);
			qI.insert(p8);
			boost::shared_ptr< QueueImplementation<int> > innerCopy(innerPtr->clone());
			impPtr = innerCopy;
	}
	qI.attachImplementation(impPtr);
	std::cout << *(qI.extract()) << std::endl;
	std::cout << *(qI.extract()) << std::endl;
	std::cout << *(qI.extract()) << std::endl;
	std::cout << *(qI.extract()) << std::endl;
	std::cout << *(qI.extract()) << std::endl;
	std::cout << *(qI.extract()) << std::endl;
	std::cout << *(qI.extract()) << std::endl;
	std::cout << *(qI.extract()) << std::endl;
	return 0;
}
