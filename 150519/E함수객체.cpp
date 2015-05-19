// 함수 객체: 함수처럼 동작하는 객체
#include <iostream>
using namespace std;

struct Adder {
	int operator() (int a, int b) { return a + b; }
};

struct Subber {
	int operator() (int a, int b) { return a - b; }
};

void main() {
	Adder add;
	cout << add(1, 2) << endl;	// add.operator()(1, 2)
	Subber sub;
	cout << sub(1, 2) << endl;	// sub.operator()(1, 2)
}

// 함수는 같은 시그니처이면 같은 타입이지만
// 객체는 같은 시그니처, 완전히 같은 구현이라도 태그(class or struct 이름)가 다르면 다른 타입