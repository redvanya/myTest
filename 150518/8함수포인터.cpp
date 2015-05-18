// 멤버 함수 포인터 이야기
#include <iostream>
using namespace std;

int foo() { return 0; }

void func() { printf("calle func()\n"); }

class Clazz {
public:
	void member_func()	// void memeber_func(Clazz* const this)
	{ printf("called member_func()\n"); }
	static void static_func() { printf("called static_func()\n"); }	// 정적 멤버 함수는 일반 함수와 같다
};

/*
sizeof는 함수가 아닌 연산자이지만 ()를 쓴다
보통은 안써도 되지만, sizeof 다음에 타입이 올 경우 ()를 꼭 써야 한다. ex: sizeof(int)
쓰고 안쓰면 헷갈리기 때문에 무조건 쓰도록 한다.
아래의 함수포인터시 클래스 함수 앞에 & 쓰는 것도 그런 맥락. (static은 안써도 되긴 하지만 그냥 멤버함수는 무조건 써야하니 헷갈리니 그냥 다 쓰는 걸로)
*/

int main() {
	void(*fp1)() = func;	// C언어에서 일반 함수는 암시적으로 함수 포인터로 변환됨
	void(*fp2)() = &Clazz::static_func;	// 정적 멤버 함수는 일반함수와 같지만 Clazz안에 갖혀있다
										// 원칙적으로 클래스 내의 멤버 함수는 암시적으로 함수 포인터로 변환되지 않지만, C언어와의 하위호환성 때문에 변환됨

	fp2();

	// 멤버 함수 포인터의 선언 방법
	// 리턴타입(클래스명::*변수명)([매개변수, ...]);
	// 멤버 함수는 암시적으로 포인터로 해석되지 않기 때문에 명시적으로 &연산자 사용
	void(Clazz::*fp3)() = &Clazz::member_func;	// 반드시 & 써야함. C++문법이기 때문

	Clazz obj;
	// fp3(&obj);	// push 0x12ff60, but this는 ECX라는 범용 레지스터에 있는 것이라 stack에 넣는다고 읽을 수 없음
	(obj.*fp3)();	// .* 이라는 연산자 사용

	Clazz* pObj = new Clazz;
	(pObj->*fp3)();	// 왼쪽의 피연산자가 포인터면 ->* 사용
	
}

/*
int main()
{
	// 포인터 변수의 선언 방법: 타입 * 변수명;
	// 함수 포인터 변수의 선언은 함수의 타입이 아닌 시그니처를 사용해서 선언해야 함
	// 시그니처 * 변수명;
	//void * fp(); // 함수를 선언
	
	// 1. 함수 포인터 변수의 선언: 리턴타입(*변수명)([매개변수, ...]);
	void(*fp)();

	// 2. 함수의 이름이 함수의 포인터로 해석됨
	fp = func;

	// 3. 함수 호출 연산자를 사용
	fp();
}*/