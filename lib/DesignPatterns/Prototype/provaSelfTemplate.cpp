#include <iostream>
#include <typeinfo>
#include "Prototype.h"

class A : public Prototype<A>
{
	private:
		int aa;
	public:
		void printA()
		{
			std::cout << "PrintA" << std::endl;
			std::cout << typeid(*this).name() << std::endl;

		}
};

class B : public A
{
	int v;
	public:
		B(int param) : v(param){}
		A* clone()
		{
			return new B(*this);
		}
		void printB()
		{
			std::cout << "PrintB, v:" << v << std::endl;
			std::cout << typeid(*this).name() << std::endl;
			printA();
		}
};

int main()
{
	B b(12);
	b.printB();
	A* ciao = b.clone();
	B* caio = dynamic_cast<B*>(ciao);
	caio->printB();
	return 0;
}
