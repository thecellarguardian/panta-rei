#include <iostream>
#include <boost/shared_ptr.hpp>
#include <list>
using namespace std;
using namespace boost;

int main()
{
	{
		shared_ptr<int> p(new int);
		*p = 3;
		{
			list< shared_ptr<int> > l;
			l.push_back(p);
			l.remove(p);
			cout << l.size() << endl;
		}
		cout << *p;
	}
	return 0;
}
