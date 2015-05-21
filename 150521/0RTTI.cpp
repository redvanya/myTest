// RTTI : RunTime Type Information -> Java에서는 reflection
// - 실행 시간에 특정 포인터 변수가 어떤 타입인지 조사하는 기술
// 조건 : 클래스가 최소한 하나 이상의 가상 함수를 포함하고 있어야 함
#include <iostream>
using namespace std;

class Animal {
public:
	virtual ~Animal() {}
};

class Dog : public Animal {
public:
	virtual ~Dog() {}
};

/*
int main() {
Animal* p1 = new Animal;	// 런타임 문법

// RTTI를 사용하기 위해 컴파일러가 typeid라는 연산자를 제공합니다.
const type_info& t1 = typeid(p1);	// typeid(변수명)
cout << t1.name() << endl;

Dog* p2 = new Dog;
const type_info& t2 = typeid(p2);
cout << t2.name() << endl;

//Animal *p3 = static_cast<Animal*>(new Dog);	// 원래 이렇게 써야 하지만 컴파일러가 컴파일 타임에 상속관계를 알기 때문에 캐스팅 생략 가능
Animal* p3 = new Dog;				// 상속관계: upcasting
const type_info& t3 = typeid(p3);
cout << t3.name() << endl;			// Animal

Dog* pDog = static_cast<Dog*>(p3);		// p3의 타입이 Animal* 이기 때문에 그 안이 Dog*라 하더라도 알 수 없음. -> downcasting 해야함.
const type_info& t4 = typeid(pDog);		// 알 수 있는 방법이 없다. 안전하게 다운캐스팅 할 수 있는 방법 필요 (아래 main)
cout << t4.name() << endl;
}
*/

int main() {
	Animal* p1 = new Animal;	// 런타임 문법

	// RTTI를 사용하기 위해 컴파일러가 typeid라는 연산자를 제공합니다.
	const type_info& t1 = typeid(p1);	// typeid(변수명)
	cout << t1.name() << endl;

	Animal a;
	const type_info& t2 = typeid(a);	// 포인터 변수와 일반 객체의 변수도 사용 가능
	cout << t2.name() << endl;	// Animal

	Animal* pAnimal = new Dog;

	const type_info& t3 = typeid(*pAnimal);		// 역참조를 하면 Dog인지 아닌지 알 수 있다
	cout << t3.name() << endl;	// Dog
	const type_info& t4 = typeid(Dog);	// 타입도 사용 가능
	cout << t4.name() << endl;	// Dog

	if (t3 == t4)	// t3.operator== 연산자 오버로딩이 되어 있다 //if (strcmp(t3.name(), t4.name()) == 0)
		cout << "같은 타입" << endl;
	else
		cout << "다른 타입" << endl;

	if (typeid(*pAnimal) == typeid(Dog))	// typeid안에 포인터 변수, 타입이 사용 가능하므로 이렇게 쓸 수 있다
		cout << "같은 타입" << endl;
	else
		cout << "다른 타입" << endl;

	// dynamic_cast 사용하면 간단하게 안전한 다운캐스팅을 할 수 있다.
	// 위의 typeid를 사용한 내용과 같은 문법을 만든 것이 dynamic_cast
	// dynamic_cast를 사용할 경우, 반드시 리턴 타입을 조사해서 사용해야한다
	// 다운캐스팅에 실패할 경우, 널이 반환되기 때문이다.
	Dog* pDog = dynamic_cast<Dog*>(pAnimal);	// 바로 사용하면 안되고, dynamic_cast의 결과값을 조사해서 null이 아닌 경우만 사용
	if (pDog)
		cout << "pAnimal is Dog" << endl;
	else
		cout << "pAnimal is not Dog" << endl;
}
