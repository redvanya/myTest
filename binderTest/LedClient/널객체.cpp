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
		//a = 0;	// this->a = 0;	-> this�� ���̴ϱ� ���⼭ �״´�
		this ? onAsFoo() : 0;	// ���� ���� �ʵ��� �ϱ� ���ؼ� this�� ��üũ�� ���ش�
	}
};

void main() {
	Clazz* p = 0;
	p->foo();	// �ȴ� -> ���� ���� �ÿ��� ���� �ʰ�, ���� ���� �����Ϸ��� �ϸ� �״´�
	//p->a = 0;	// �״´�
}