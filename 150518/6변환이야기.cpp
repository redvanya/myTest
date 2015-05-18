// 변환의 위험성
#include <iostream>
using namespace std;

#if 1
class Complex {
public:
	int r, i;

	Complex(int a = 0, int b = 0) : r(a), i(b) {}

	// 연산자 오버로딩
	// 어떤 클래스가 변환 연산자를 사용할 것이라면 가급적 변환 연산자 보다는
	// 변환 인터페이스를 제공하는 것이 더 나을 수 있다.
	explicit operator int() { return r; }	// return 타입이 있더라도 지우자. 그 당시 구현으로 어려웠다
	int asReal() { return r; }
};

void foo(int i) {
	cout << "called foo(" << i << ")" << endl;
}

int main() {
	double d = 3.14;
	int i = d;	// 기본 데이터에 한해서 데이터 손실이 있더라도 암시적 변환이 일어난다. standard conversion(기본변환)
	foo(i);		// cout << i << endl;

	Complex c(1, 1);	// 1 + 1i
	int real = c;		// 이성적으로, 허수는 저장이 안되어도 실수는 저장되어야 하지 않나? 사용자 정의 타입도 기본타입과 같이 동작하도록 문법적으로 지원
						// int(c) -> c.operator int();
						// 변환 연산자 쓰지 말라 ? 버그가 있다
	// cout << real << endl;
	foo(c);		// 되면 안되는데 된다! 버그 - 우리가 의도하지 않은 코드. explicit 쓰면 제한할 수 있음
}
#endif

#if 0
class Int32 {
public:
	int val;
	// 변환 생성자는 인자가 하나인 생성자는 모두 변환 생성자가 될 수 있다
	// 변환 생성자는 컴파일러에 의해 호출될 수 있다 (암시적 변환)
	// 인자가 하나인 생성자의 변환 생성자로써 사용을 금지하려면 explicit
	explicit Int32(int i = 0): val(i) {}
	
};

void foo(Int32 i){
	cout << "called foo(" << i.val << ")" << endl;

}

void main() {
	Int32 i(20);
	// coutn << i.val << endl;
	foo(i);	// OK

	int n = 30;
	foo(n); // foo(Int32(n)); -> 되는데 되면 안됨! 원하지 않은 동작
}
#endif