#include <iostream>
using namespace std;

#if 0	// ���ε�
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
	p1->cry();	// cry(p1); -> p1Ÿ���� Animal*, ���� Animal�� cry�� ���ε� ��.

	getchar();

	Animal* p2 = new Dog;
	p2->cry();	// cry(p2); -> p2Ÿ���� Animal*, ���� Animal�� cry�� ���ε� ��.
				// �θ� Ÿ���� �Լ��� virtual�� �����ָ� Dog�� cry�� ���ε� ��.
				// Java�� ���� ���ε��� �⺻�̶� �ڵ����� Dog cry������, C++�� C�� �⺻���� �ϱ� ������ ���� ���ε��� �⺻
}
#endif

#if 0
// ���� �Լ� ���̺� ����
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


#if 1	// �߻�Ŭ����
// �߻�Ŭ����: ���� ���� �Լ��� �� �� �̻� ������ �ִ� Ŭ������ �ǹ�
// C++�� �̷��� �Լ��� ����θ� ���� �߻� Ŭ�������� �� �� ����
// Java�� �׷� ���� ��ȣ�ؼ� �ƿ� abstract��� Ű���带 class�տ� �ٿ��� ��Ȯ�ϰ� �߻�Ŭ���� ���� ��Ÿ��
class Parent {
public:
	//virtual void foo() {}
	virtual void foo() = 0;	// ���� ���� �Լ� : �Լ� ��ü�� ���ǵ��� ���� �Լ� -> �̰��� ������ �߻� Ŭ����
};

class Child : public Parent {

};

void main() {
	Parent p;	// �߻� Ŭ������ ��ü�� ������ �� ����.
	Child c;	// �ڽ��� �θ� ��� �޾Ҵµ�, �θ��� ���������Լ��� �������� �ʾҴٸ� �ڽĵ� �߻�Ŭ������ �ȴ�
}
#endif