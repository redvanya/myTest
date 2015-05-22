
#include <iostream>
using namespace std;

class Clazz
{
	int a;

protected:
	void onAsFoo() { cout << "foo" << endl; }

public:
	void foo() { // void foo(Clazz* const this)
		this ? onAsFoo() : 0;
	}
};

void main()
{
	Clazz* p = 0;
	p->foo();
}