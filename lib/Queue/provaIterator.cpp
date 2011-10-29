#include <list>
#include <iostream>

class Queue : public std::list<int>
{
	public:
		class iterator
		{
			private:
				std::list<int>::iterator realIterator;
			public:
				iterator(std::list<int>::iterator i) : realIterator(i){}
				const iterator& operator++(int i)
				{
					realIterator++;
					return *this;
				}
				int& operator*()
				{
					return *realIterator;
				}
				void operator=(iterator& assign)
				{
					realIterator = assign.realIterator;
				}
				bool operator!=(iterator compare)
				{
					return realIterator != compare.realIterator;
				}
		};
		iterator begin(){iterator i(std::list<int>::begin()); return i;};
		iterator end(){iterator i(std::list<int>::end()); return i;};
};

int main()
{
	Queue q;
	q.push_back(3);
	q.push_back(4);
	q.push_back(5);
	Queue::iterator i = q.begin();
	(*i)++;
	for(; i != q.end(); i++)
	{
		std::cout << *i << std::endl;
	}
	return 0;
}
