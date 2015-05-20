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
	void use_phone(Anycall* c, const char* n) { c->send(n); }	// AnyCall이 추가되자, Person Class 가 수정됨. 객체지향에 위배됨
	//  tightly coupling때문 -> 새로운 객체를 추가하여 loose coupling으로 만들자
};

void main() {
	Person p;

	Cyon c;
	p.use_phone(&c, "000-0000-0000");

	Anycall a;
	p.use_phone(&a, "000-0000-0000");
}
#endif

// 모든 핸드폰이 지켜야 할 규칙을 클래스로 구현합니다.
// C++에서는 인터페이스를 식별하기 위한 키워드를 제공하지 않는다
// 그래서 접두어로 I(Interface)를 붙이는 관례가 있다.
#define interface struct	// .h에 이런식으로 해두면 interface라는 명칭을 쓸 수 있다
interface IPhone {
	// 순수 가상 함수는 자식에게 어떠한 기능을 강제로 구현하도록 하기 위한 문법적인 장치이다
	virtual void call(const char* n) = 0;	// 어차피 public이므로, 인터페이스는 구조체로 많이 구현된다. 굳이 class쓸 필요 없다.
	// 안드로이드 프레임웍에서는 class를 사용한다.
};

// 이제 핸드폰을 설계하는 사람은 Phone을 상속받기로 약속한다
class Anycall : public IPhone {
public:
	//void send(const char* n) { printf("calling %s with Anycall\n", n); }
	void call(const char* n) { printf("calling %s with Anycall\n", n); }	// 이게 없으면 객체 생성이 안되기에 어쩔 수 없이 구현
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

// C++에서는 인터페이스인지 아닌지 알 수있는 명칭이 없다.
// -> 그래서 관례적으로 I 를 붙인다. ex) IBinder, IInterface, ... I로 시작하면 인터페이스다!