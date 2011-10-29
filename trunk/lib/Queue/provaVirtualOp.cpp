#include <iostream>

class A
{
	public:
		virtual const A& operator++(int) = 0;
};

class B : public A
{
	public:
		const A& operator++(int)
		{
			std::cout << "OK" << std::endl;
			return *this;
		}
};

int main()
{
	A* a = new B();
	a->operator++(1);
	return 0;
}
