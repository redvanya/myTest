// 1. SP : Strong Pointer
// 2. WP : Weak Pointer
// 3. UniquePtr : ���ø� ����ȭ, ������ȭ, �κ�����ȭ -> ���ø� ��� ����

// ��ü�� ���� ��å�� ������ ��, ����Ʈ ������ ���� ����
// 1. ���� ���� (shallow copy)
// 2. ���� ����
// 3. ���� ���� <- Unique_ptr
// 4. *������ ���� ��å <- auto_ptr
// 5. *���� ��� ��� <- share_ptr 
#include <iostream>
using namespace std;

#if 0 // 1. ���� ���� (shallow copy)
class Point {
public:
	int x, y;
	Point(int a = 0, int b = 0) : x(a), y(b) {}

	// ���� ���� ��å
	Point(const Point& p) : x(p.x), y(p.y) { cout << "Point(Point)" << endl; }
};

int main() {
	Point p1(1, 1);
	Point p2 = p1;	// Point p2(p1); -> �⺻ ���� �������� ��å: ���� ����
}
#endif

#include <cstring>

#if 0 // 2. ���� ������ ������ -> ���� ����
class Person {
	char* name;
	int age;
public:
	// "hello" -> h e l l \0
	Person(const char* n, int a) : age(a) {
		name = new char[strlen(n) + 1];
								//  ^ : NULL
		strcpy(name, n); // null���� �����ؼ� copy�Ѵ�. null�� �� üũ�ϱ�
	}

	~Person() { delete[] name; }

	// ���� ���� ��å�� ���� ������
	Person(const Person& p) : age(p.age) {
		// ���� �Ҵ�� ��ü�� ���� ����
		name = new char[strlen(p.name) + 1];
		strcpy(name, p.name);
	}
	
};

int main() {
	Person p1("kkk", 20);
	Person p2 = p1;	// ���� ������ ȣ�� : ���� ���� - �����Ϸ��� ������ ���������, name�� �������� ����
	// ��Ÿ�� ���� : double free(������) - p2�� �Ҹ��ڷ� name�� �����ϱ� ������, p1�� dangling pointer�� ��.
	// ���⼭ ���� �޸𸮸� free�Ϸ� �ϴ� segmentation fault.
	// �ذ� : ���� ����
	getchar();
}
#endif

#if 1 // 3. ������ ���� ���
class Person {
	char* name;
	int age;
public:
	Person(const char* n, int a) : age(a) {
		name = new char[strlen(n) + 1];
		strcpy(name, n);
	}

	~Person() { delete[] name; }

	// ������ ���� ��å�� ���� ������
	Person(Person& p) : age(p.age), name(p.name) {	// �ϴ� ���� ���� ���� ��
		// ������ ����
		p.name = 0;
		p.age = 0;
	}
	// ���� ����? swap �ÿ� ���� ���縦 3���̳� �����ϸ�, ���� �Ҵ��� ������ �ؾ� �ϴ� ���ɻ��� ������ ����.
	// -> �������������� �ϸ� ���� ����� ����Ǵ� ������ ���� swap�� ��
	// move constructor: ������ C++������ ���� �����ϴ� �ƿ� ���Ե�.
};

int main() {
	Person p1("kkk", 20);
	Person p2 = p1;
	// p1�� �Ҹ��� �Ҹ� �� ���� ���� ? 0����(NULL)�� OS�������� ���� �� ���� �Ѿ. ������
	// ���⼭ p1.name �ϸ�? �״´�. �ذ� ����� ����. ������ ���� ������ �� �˰� �� ��� �Ѵ�.
	getchar();
}
#endif
