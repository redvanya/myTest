#include <iostream>
using namespace std;

#if 0	// 바인딩
class Animal {
public:
	virtual void cry() {	// void Animal::cry(Animal* const this)
		cout << "Animal::cry()" << endl;
	}
};

class Dog : public Animal {
public:
	void cry() {	// void Dog::cry(Dog* const this)
		cout << "Dog::cry()" << endl;
	}
};

int main() {
	Animal* p1 = new Animal;
	p1->cry();	// cry(p1); -> p1타입이 Animal*, 따라서 Animal의 cry가 바인딩 됨.

	getchar();

	Animal* p2 = new Dog;
	p2->cry();	// cry(p2); -> p2타입이 Animal*, 따라서 Animal의 cry가 바인딩 됨.
				// 부모 타입의 함수에 virtual을 적어주면 Dog의 cry로 바인딩 됨.
				// Java는 동적 바인딩이 기본이라서 자동으로 Dog cry되지만, C++은 C를 기본으로 하기 때문에 정적 바인딩이 기본
}
#endif

#if 0
// 가상 함수 테이블 존재
class Parent {
	int val;
public:
	virtual ~Parent() {}
};

void main() {
	Parent p;
	cout << sizeof p << endl;
}
#endif


#if 1	// 추상클래스
// 추상클래스: 순수 가상 함수를 한 개 이상 가지고 있는 클래스를 의미
// C++은 이렇듯 함수의 선언부를 봐야 추상 클래스인지 알 수 있음
// Java는 그런 것이 모호해서 아예 abstract라는 키워드를 class앞에 붙여서 명확하게 추상클래스 임을 나타냄
class Parent {
public:
	//virtual void foo() {}
	virtual void foo() = 0;	// 순수 가상 함수 : 함수 몸체가 정의되지 않은 함수 -> 이것이 있으면 추상 클래스
};

class Child : public Parent {

};

void main() {
	Parent p;	// 추상 클래스는 객체를 생성할 수 없다.
	Child c;	// 자식이 부모를 상속 받았는데, 부모의 순수가상함수를 구현하지 않았다면 자식도 추상클래스가 된다
}
#endif