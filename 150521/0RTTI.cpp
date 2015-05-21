// RTTI : RunTime Type Information -> Java������ reflection
// - ���� �ð��� Ư�� ������ ������ � Ÿ������ �����ϴ� ���
// ���� : Ŭ������ �ּ��� �ϳ� �̻��� ���� �Լ��� �����ϰ� �־�� ��
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
Animal* p1 = new Animal;	// ��Ÿ�� ����

// RTTI�� ����ϱ� ���� �����Ϸ��� typeid��� �����ڸ� �����մϴ�.
const type_info& t1 = typeid(p1);	// typeid(������)
cout << t1.name() << endl;

Dog* p2 = new Dog;
const type_info& t2 = typeid(p2);
cout << t2.name() << endl;

//Animal *p3 = static_cast<Animal*>(new Dog);	// ���� �̷��� ��� ������ �����Ϸ��� ������ Ÿ�ӿ� ��Ӱ��踦 �˱� ������ ĳ���� ���� ����
Animal* p3 = new Dog;				// ��Ӱ���: upcasting
const type_info& t3 = typeid(p3);
cout << t3.name() << endl;			// Animal

Dog* pDog = static_cast<Dog*>(p3);		// p3�� Ÿ���� Animal* �̱� ������ �� ���� Dog*�� �ϴ��� �� �� ����. -> downcasting �ؾ���.
const type_info& t4 = typeid(pDog);		// �� �� �ִ� ����� ����. �����ϰ� �ٿ�ĳ���� �� �� �ִ� ��� �ʿ� (�Ʒ� main)
cout << t4.name() << endl;
}
*/

int main() {
	Animal* p1 = new Animal;	// ��Ÿ�� ����

	// RTTI�� ����ϱ� ���� �����Ϸ��� typeid��� �����ڸ� �����մϴ�.
	const type_info& t1 = typeid(p1);	// typeid(������)
	cout << t1.name() << endl;

	Animal a;
	const type_info& t2 = typeid(a);	// ������ ������ �Ϲ� ��ü�� ������ ��� ����
	cout << t2.name() << endl;	// Animal

	Animal* pAnimal = new Dog;

	const type_info& t3 = typeid(*pAnimal);		// �������� �ϸ� Dog���� �ƴ��� �� �� �ִ�
	cout << t3.name() << endl;	// Dog
	const type_info& t4 = typeid(Dog);	// Ÿ�Ե� ��� ����
	cout << t4.name() << endl;	// Dog

	if (t3 == t4)	// t3.operator== ������ �����ε��� �Ǿ� �ִ� //if (strcmp(t3.name(), t4.name()) == 0)
		cout << "���� Ÿ��" << endl;
	else
		cout << "�ٸ� Ÿ��" << endl;

	if (typeid(*pAnimal) == typeid(Dog))	// typeid�ȿ� ������ ����, Ÿ���� ��� �����ϹǷ� �̷��� �� �� �ִ�
		cout << "���� Ÿ��" << endl;
	else
		cout << "�ٸ� Ÿ��" << endl;

	// dynamic_cast ����ϸ� �����ϰ� ������ �ٿ�ĳ������ �� �� �ִ�.
	// ���� typeid�� ����� ����� ���� ������ ���� ���� dynamic_cast
	// dynamic_cast�� ����� ���, �ݵ�� ���� Ÿ���� �����ؼ� ����ؾ��Ѵ�
	// �ٿ�ĳ���ÿ� ������ ���, ���� ��ȯ�Ǳ� �����̴�.
	Dog* pDog = dynamic_cast<Dog*>(pAnimal);	// �ٷ� ����ϸ� �ȵǰ�, dynamic_cast�� ������� �����ؼ� null�� �ƴ� ��츸 ���
	if (pDog)
		cout << "pAnimal is Dog" << endl;
	else
		cout << "pAnimal is not Dog" << endl;
}
