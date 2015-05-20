#include <iostream>
using namespace std;

#if 0
class Anycall {
public:
	void send(const char* n) { printf("calling %s with Anycall\n", n); }
};

class Cyon {
public:
	void call(const char* n) { printf("calling %s with Cyon\n", n); }
};

class Person {
public:
	void use_phone(Cyon* c, const char* n) { c->call(n); }
	void use_phone(Anycall* c, const char* n) { c->send(n); }	// AnyCall�� �߰�����, Person Class �� ������. ��ü���⿡ �����
	//  tightly coupling���� -> ���ο� ��ü�� �߰��Ͽ� loose coupling���� ������
};

void main() {
	Person p;

	Cyon c;
	p.use_phone(&c, "000-0000-0000");

	Anycall a;
	p.use_phone(&a, "000-0000-0000");
}
#endif

// ��� �ڵ����� ���Ѿ� �� ��Ģ�� Ŭ������ �����մϴ�.
// C++������ �������̽��� �ĺ��ϱ� ���� Ű���带 �������� �ʴ´�
// �׷��� ���ξ�� I(Interface)�� ���̴� ���ʰ� �ִ�.
#define interface struct	// .h�� �̷������� �صθ� interface��� ��Ī�� �� �� �ִ�
interface IPhone {
	// ���� ���� �Լ��� �ڽĿ��� ��� ����� ������ �����ϵ��� �ϱ� ���� �������� ��ġ�̴�
	virtual void call(const char* n) = 0;	// ������ public�̹Ƿ�, �������̽��� ����ü�� ���� �����ȴ�. ���� class�� �ʿ� ����.
	// �ȵ���̵� �����ӿ������� class�� ����Ѵ�.
};

// ���� �ڵ����� �����ϴ� ����� Phone�� ��ӹޱ�� ����Ѵ�
class Anycall : public IPhone {
public:
	//void send(const char* n) { printf("calling %s with Anycall\n", n); }
	void call(const char* n) { printf("calling %s with Anycall\n", n); }	// �̰� ������ ��ü ������ �ȵǱ⿡ ��¿ �� ���� ����
};

class Cyon : public IPhone {
public:
	void call(const char* n) { printf("calling %s with Cyon\n", n); }
};

class Person {
public:
	void use_phone(IPhone* c, const char* n) { c->call(n); }
};

void main() {
	Person p;

	Cyon c;
	p.use_phone(&c, "000-0000-0000");

	Anycall a;
	p.use_phone(&a, "000-0000-0000");
}

// C++������ �������̽����� �ƴ��� �� ���ִ� ��Ī�� ����.
// -> �׷��� ���������� I �� ���δ�. ex) IBinder, IInterface, ... I�� �����ϸ� �������̽���!