// template
// C++ 이란	1. 절차지향적 : C를 subset으로 가지고 있기 때문
//			2. 객체지향적 : +a로 객체 지향 개념을 포함한다
//			3. 일반화 프로그래밍 : 템플릿
//			4. 메타 프로그래밍 : 템플릿 도입 - factorial같은 재귀적으로 구하는 것을 컴파일 타임에 구할 수 있다. 성능상의 오버헤드가 없다
//							   자바에서도 비슷하게 generic을 도입했다

#include <iostream>
using namespace std;

#if 0
// 1. 함수 템플릿
template<typename T> T Max(T a, T b) { return a > b ? a : b; }

// 2. 클래스 템플릿
template<typename T> class Stack {
	T* arr;
public:
	void push_front(T data) {}
};

void main() {
	cout << Max<int>(1, 2) << endl;	// 원래 꼭 타입을 넘겨줘야 한다 - 명시적 타입 지정
	cout << Max(1, 2) << endl;		// 타입을 생략해도 컴파일러가 사용된 인자의 타입을 확인해서 템플릿을 만든다 - 암시적 추론 가능

	//Stack s;		// ERROR, 클래스 템플릿은 암시적 추론 불가능
	Stack<int> s;	// OK, 클래스 템플릿은 타입을 명시적으로 사용해야 한다. Stack은 템플릿이고 Stack<int>는 고유한 타입
	s.push_front(20);
}
#endif

#if 0
// 템플릿 버전
// 주템플릿/기본 템플릿 (primary template) : 모든 타입이 다 된다.
template<typename T> class Stack {
public:
	void push() { cout << "T" << endl; }
};

// 부분 전문화 템플릿 (partial specializer) : 하나의 타입으로 오버로딩 가능
// 특정 타입에 대해서만 다르게 동작하도록 하고 싶다
template<typename T> class Stack<T*> {
public:
	void push() { cout << "T*" << endl; }
};

// 전문화 템플릿 (specializer)
template<> class Stack<char*> {
public:
	void push() { cout << "char*" << endl; }
};

int main() {
	Stack<int> s1;	s1.push();
	Stack<int*> s2;	s2.push();
	Stack<char*> s3;	s3.push();
}
#endif

// 템플릿 메타 프로그래밍 : 구현에 제한이 많기 때문에 아직까지는 학문적으로만 쓰임.

// 런타임에 동작하는 함수
int fact(int n) {
	if (n <= 1)	return 1;
	return n * fact(n - 1);
}

// 모든 정수 N에 대해서 처리하는 클래스 생성
template<int N> struct Fact {
	enum { num = N * Fact<N - 1>::num };
};

// N이 1인 경우에 대한 처리는 전문화 사용
template<> struct Fact < 1 > {
	enum { num = 1 };
};

void main() {
	//cout << fact(5) << endl;	// 런타임 동작
	cout << Fact<5>::num << endl;	// 컴파일 타임에 계산 완료
	
}