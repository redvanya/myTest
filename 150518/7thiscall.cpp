#include <iostream>
using namespace std;

#if 0
class Int32 {
public:
	int val;

	// C++ �Լ� ȣ�� �Ծ�: __thiscall
	// -> �Լ��� ȣ��� ��, ��ü�� �ּҰ� ���޵Ǵ� ���
	void setValue(int v)	// void Int32::setValue(Int32* const this, int v)
	{ val = v; }			// this->val = v;
};

void main() {
	Int32 i32;
	cout << sizeof i32 << endl;

	i32.setValue(10);	// Int32::setValue(&i32, 10); - �����ϰ� ���ϸ� stack(parameter ����)�� �ƴ϶� ���� �������� ecx�� ����ȴ�.
	cout << i32.val << endl;
}
#endif

// ���� ����� �Ϲ� ���

class Clazz {
	int member;
	static int static_member;	// Clazz��� namespace �ȿ� ���� ���� ����(����), ���� �� ��!

public:
	// �Ϲ� ��� �Լ�
	// �Ϲ� ����� ���� ����
	// ���� ����� ���� ����
	void member_func() {	// void member_func(Clazz* const this)
		member = 0;			// this�� ������ �����, ���������� ���� ����
		static_member = 0;

		//member_func();	// this->member_func()
		//static_func();	// OK
	}

	// ���� ��� �Լ�: C ����� �Ϲ� �Լ��� ����
	static void static_func() {	// void static_func()
//		member = 0;			// ERROR, this->member = 0; this�� ������ �Ϲ� ��� ���� ������ �ȵȴ�
		static_member = 0;	// OK
		
		//member_func(); // ERROR
		//static_func();
	}
};
int Clazz::static_member = 0;	// ���Ǹ� ���� ����� ��. C�� �� ���� Ű���带 ���ؼ� ��ü����� ����� ���� �̷� ������ ���� ����.

// static Ű����� ��ü�� ���Ե��� �ʴ� ���� �ɺ��� ������ ��, ���

void main() {
	Clazz obj;
	obj.member_func();

	Clazz::static_func();	// JAVA: Clazz.static_func();
}