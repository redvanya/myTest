#include <iostream>
using namespace std;

class Clazz {
protected:
	void onAsFoo() {
		cout << "asFoo" << endl;
	}
public:
	int a;
	void foo() {	// void foo(Clazz* const this)
		//cout << "foo" << endl;
		//a = 0;	// this->a = 0;	-> this가 널이니까 여기서 죽는다
		this ? onAsFoo() : 0;	// 절대 죽지 않도록 하기 위해서 this의 널체크를 해준다
	}
};

void main() {
	Clazz* p = 0;
	p->foo();	// 된다 -> 널을 참조 시에는 죽지 않고, 널의 값을 변경하려고 하면 죽는다
	//p->a = 0;	// 죽는다
}