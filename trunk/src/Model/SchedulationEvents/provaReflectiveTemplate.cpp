#include <iostream>
#include <typeinfo>

enum Type
{
	TYPE_ONE,
	TYPE_TWO,
	TYPE_THREE
};

template <enum Type> class ReflectiveTemplate
{
	public:
		void print()
		{
			std::cout << typeid(this).name() << std::endl;
		}
};

int main()
{
	ReflectiveTemplate<TYPE_ONE> first;
	ReflectiveTemplate<TYPE_TWO> second;
	ReflectiveTemplate<TYPE_THREE> third;
	first.print();
	second.print();
	third.print();
	return 0;
}
