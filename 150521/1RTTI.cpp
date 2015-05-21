// RTTI의 구현 요소 1. 클래스의 이름을 저장
//				   2. 클래스의 이름을 읽기

#include <iostream>
#include <string>
using namespace std;

#if 0
class Animal {
public:
	virtual ~Animal() {}
	// 이름을 저장하기 위해 전역 변수 사용
	static const string descriptor;	// 아직 메모리가 할당되지 않았기에 초기화 할 수 없다

	// 이름을 꺼내오기 위한 인터페이스 제공
	virtual const string& getInterfaceDescriptor() {
		return descriptor;
	}
};
const string Animal::descriptor = "Animal";

class Dog : public Animal {
public:
	static const string descriptor;
	const string& getInterfaceDescriptor() {
		return descriptor;
	}
};
const string Dog::descriptor = "Dog";

int main() {
	Animal* pAnimal = new Animal;
	//if (typeid(*pAnimal) == typeid(Animal))
	//	cout << "pAnimal is Animal" << endl;
	//if (pAnimal->getInterfaceDescriptor() == Animal::descriptor)	// 우리가 만든 RTTI 클래스가 typeid와 같은 결과인지 보자
	//	cout << "pAnimal is Animal" << endl;

	Animal* p2 = new Dog;
	cout << p2->getInterfaceDescriptor() << endl;
	if (p2->getInterfaceDescriptor() == Dog::descriptor)
		cout << "pAnimal is Dog" << endl;
	
}
#endif
// http://androidxref.com/5.1.0_r1/xref/frameworks/native/include/binder/IInterface.h#74

#define String16 string	// Java에서의 2byte의 유니코드를 호환하기 위해 C++에서 만든 클래스
// RTTI의 선언부 코드 (어딘가의 .h에 두면 된다)
#define DECLARE_META_INTERFACE(INTERFACE)			\
	static const String16 descriptor;					\
	virtual const String16& getInterfaceDescriptor();
// RTTI의 구현부 코드 (어딘가의 .h에 두면 된다) - 매크로의 #의 역할은 토큰을 문자열화 해주는 것
#define IMPLEMENT_META_INTERFACE(INTERFACE, NAME)			\
const String16 INTERFACE::descriptor(NAME);		\
const String16& INTERFACE::getInterfaceDescriptor() { return descriptor; }

class Animal {
public:
	DECLARE_META_INTERFACE(Animal)
};
IMPLEMENT_META_INTERFACE(Animal, "Animal")	// 첫번째 인자는 클래스 이름, 두번째 인자는 이름을 써준다

class Dog : public Animal {
public:
	DECLARE_META_INTERFACE(Dog)
};
IMPLEMENT_META_INTERFACE(Dog, "Dog")

int main() {
	Animal* p2 = new Dog;
	cout << p2->getInterfaceDescriptor() << endl;
	if (p2->getInterfaceDescriptor() == Dog::descriptor)
		cout << "pAnimal is Dog" << endl;
}