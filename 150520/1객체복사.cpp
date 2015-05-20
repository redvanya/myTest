// ��ü ���� ��å
// 1. ���� ���� (shallow copy)	 : C++�⺻ ��å����, �����Ҵ�� ��ü�� ���簡 ���� �ʴ´�.
//								   ���� �����͸� ������� ��ȿ�� ��ü���� �� �� ���� ������ double free�� �߻�
// 2. ���� ����					 : ���� �Ҵ� ��ü�� ���������, new ���� ����� ũ�� �纻�� ���ܼ� �޸𸮰� ����ȴ�. ���� �й������θ� ���� ������ ����� ���� ����.
// 3. ���� ���� (Unique_ptr)		 : ��������ڸ� private���� ����
// 4. *������ ���� ��å (auto_ptr) : ���� ���� ��ó�� ��������, ��ü�� swap�ÿ� �޸� ������带 �ٿ��ش�.
//								   �̰��� �ſ� ���Ƽ� ������ C++������ �ƿ� �̵� �����ڷ� ������ ������ ��.
// 5. *���� ��� ��� (share_ptr)	 : ���� ���� -> ī���� �ϰ� �ִ� ���� ������ ����

// 5. ���� ��� ����� ���� ��å
#include <iostream>
#include <cstring>
using namespace std;

//class Ref {
//	static int refCount;
//	friend class Person;
//};
//int Ref::refCount = 0;

class Person {
	char* name;
	int age;
	//Ref ref;
	int* ref;

public:
	Person(const char* n, int a) : age(a), ref(new int(1)) {
		name = new char[strlen(n) + 1];
		strcpy(name, n);
		//ref.refCount++;
	}
	
	// ���� ��� ����� ���� ��å
	Person(const Person& o) : name(o.name), age(o.age), ref(o.ref) {	// ���� ���� ���
		// ���� ��� ����
		++(*ref);
	}

	~Person() {
		//ref.refCount--;
		//if (ref.refCount == 0)
		if (--(*ref) == 0) {
			delete[] name;
			delete ref;
		}			
	}
};

void main() {
	Person p1("kkk", 10);
	Person p2 = p1;
}