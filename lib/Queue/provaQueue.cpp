#include "QueueInterface/QueueInterface.h"
#include "QueueImplementation/QueueImplementation.h"
#include "QueueImplementationProvider/QueueImplementationProvider.h"
#include "Implementations/OrderedQueueImplementation/OrderedQueueImplementation.h"
#include <boost/shared_ptr.hpp>
#include <iostream>

class ParticularClass
{
	private:
		int value;
	public:
		ParticularClass(int v) : value(v) {}
		const int getValue(){return value;}
		void print()
		{
			std::cout << value << std::endl;
		}
};

class ParticularClassComparator
{
	public:
		bool operator()(boost::shared_ptr<ParticularClass>& a, boost::shared_ptr<ParticularClass>& b)
		{
			return (a->getValue() < b->getValue());
		}
};

class ParticularQueueImplementationProvider : public QueueImplementationProvider<ParticularClass>
{
	public:
		boost::shared_ptr< QueueImplementation<ParticularClass> > getImplementation()
		{
			boost::shared_ptr< QueueImplementation<ParticularClass> > implementationToReturn
				(
					new OrderedQueueImplementation
					<ParticularClass, ParticularClassComparator>()
				);
			return implementationToReturn;
		}
};

int main()
{
	ParticularQueueImplementationProvider provider;
	QueueInterface<ParticularClass> interface(&provider);
	int value = 0;
	std::cout << "Inserimenti:" << std::endl;
	for(int i = 0; i < 10; i++)
	{
		std::cin >> value;
		boost::shared_ptr<ParticularClass> p(new ParticularClass(value));
		interface.insert(p);
	}
	std::cout << "Estrazioni:" << std::endl;
	for(int i = 0; i < 10; i++)
	{
		boost::shared_ptr<ParticularClass> extracted(interface.extract());
		extracted->print();
	}
	return 0;
}
