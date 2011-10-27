#include <boost/shared_ptr.hpp>
#include <iostream>
#include <cassert>

class A
{
	public:
		~A()
		{
			std::cout << "Distruttore" << std::endl;
		}
};

int main()
{
	boost::shared_ptr<A> p(new A());
	boost::shared_ptr<A> q;
	p = q;
	assert(p.get() == NULL);
	return 0;
}
