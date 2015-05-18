#include <iostream>
using namespace std;

#if 0
class Int32 {
public:
	int val;

	// C++ 함수 호출 규약: __thiscall
	// -> 함수가 호출될 때, 객체의 주소가 전달되는 방식
	void setValue(int v)	// void Int32::setValue(Int32* const this, int v)
	{ val = v; }			// this->val = v;
};

void main() {
	Int32 i32;
	cout << sizeof i32 << endl;

	i32.setValue(10);	// Int32::setValue(&i32, 10); - 엄밀하게 말하면 stack(parameter 저장)이 아니라 범용 레지스터 ecx에 저장된다.
	cout << i32.val << endl;
}
#endif

// 정적 멤버와 일반 멤버

class Clazz {
	int member;
	static int static_member;	// Clazz라는 namespace 안에 갖힌 전역 변수(전역), 선언만 한 것!

public:
	// 일반 멤버 함수
	// 일반 멤버에 접근 가능
	// 정적 멤버에 접근 가능
	void member_func() {	// void member_func(Clazz* const this)
		member = 0;			// this가 있으니 멤버도, 전역변수도 접근 가능
		static_member = 0;

		//member_func();	// this->member_func()
		//static_func();	// OK
	}

	// 정적 멤버 함수: C 언어의 일반 함수와 동일
	static void static_func() {	// void static_func()
//		member = 0;			// ERROR, this->member = 0; this가 없으니 일반 멤버 변수 접근이 안된다
		static_member = 0;	// OK
		
		//member_func(); // ERROR
		//static_func();
	}
};
int Clazz::static_member = 0;	// 정의를 따로 해줘야 함. C에 몇 개의 키워드를 더해서 객체지향언어를 만들다 보니 이런 불편한 점이 생김.

// static 키워드는 객체의 포함되지 않는 전역 심볼을 생성할 때, 사용

void main() {
	Clazz obj;
	obj.member_func();

	Clazz::static_func();	// JAVA: Clazz.static_func();
}