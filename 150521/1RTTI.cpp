// RTTI�� ���� ��� 1. Ŭ������ �̸��� ����
//				   2. Ŭ������ �̸��� �б�

#include <iostream>
#include <string>
using namespace std;

#if 0
class Animal {
public:
	virtual ~Animal() {}
	// �̸��� �����ϱ� ���� ���� ���� ���
	static const string descriptor;	// ���� �޸𸮰� �Ҵ���� �ʾұ⿡ �ʱ�ȭ �� �� ����

	// �̸��� �������� ���� �������̽� ����
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
	//if (pAnimal->getInterfaceDescriptor() == Animal::descriptor)	// �츮�� ���� RTTI Ŭ������ typeid�� ���� ������� ����
	//	cout << "pAnimal is Animal" << endl;

	Animal* p2 = new Dog;
	cout << p2->getInterfaceDescriptor() << endl;
	if (p2->getInterfaceDescriptor() == Dog::descriptor)
		cout << "pAnimal is Dog" << endl;
	
}
#endif
// http://androidxref.com/5.1.0_r1/xref/frameworks/native/include/binder/IInterface.h#74

#define String16 string	// Java������ 2byte�� �����ڵ带 ȣȯ�ϱ� ���� C++���� ���� Ŭ����
// RTTI�� ����� �ڵ� (����� .h�� �θ� �ȴ�)
#define DECLARE_META_INTERFACE(INTERFACE)			\
	static const String16 descriptor;					\
	virtual const String16& getInterfaceDescriptor();
// RTTI�� ������ �ڵ� (����� .h�� �θ� �ȴ�) - ��ũ���� #�� ������ ��ū�� ���ڿ�ȭ ���ִ� ��
#define IMPLEMENT_META_INTERFACE(INTERFACE, NAME)			\
const String16 INTERFACE::descriptor(NAME);		\
const String16& INTERFACE::getInterfaceDescriptor() { return descriptor; }

class Animal {
public:
	DECLARE_META_INTERFACE(Animal)
};
IMPLEMENT_META_INTERFACE(Animal, "Animal")	// ù��° ���ڴ� Ŭ���� �̸�, �ι�° ���ڴ� �̸��� ���ش�

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