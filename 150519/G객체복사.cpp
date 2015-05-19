// 1. SP : Strong Pointer
// 2. WP : Weak Pointer
// 3. UniquePtr : 템플릿 전문화, 주전문화, 부분전문화 -> 템플릿 배운 이후

// 객체의 복사 정책을 이해한 후, 스마트 포인터 이해 가능
// 1. 얕은 복사 (shallow copy)
// 2. 깊은 복사
// 3. 복사 금지 <- Unique_ptr
// 4. *소유권 이전 정책 <- auto_ptr
// 5. *참조 계수 기반 <- share_ptr 
#include <iostream>
using namespace std;

#if 0 // 1. 얕은 복사 (shallow copy)
class Point {
public:
	int x, y;
	Point(int a = 0, int b = 0) : x(a), y(b) {}

	// 얕은 복사 정책
	Point(const Point& p) : x(p.x), y(p.y) { cout << "Point(Point)" << endl; }
};

int main() {
	Point p1(1, 1);
	Point p2 = p1;	// Point p2(p1); -> 기본 복사 생성자의 정책: 얕은 복사
}
#endif

#include <cstring>

#if 0 // 2. 얕은 복사의 문제점 -> 깊은 복사
class Person {
	char* name;
	int age;
public:
	// "hello" -> h e l l \0
	Person(const char* n, int a) : age(a) {
		name = new char[strlen(n) + 1];
								//  ^ : NULL
		strcpy(name, n); // null까지 포함해서 copy한다. null을 꼭 체크하기
	}

	~Person() { delete[] name; }

	// 깊은 복사 정책의 복사 생성자
	Person(const Person& p) : age(p.age) {
		// 동적 할당된 객체는 깊은 복사
		name = new char[strlen(p.name) + 1];
		strcpy(name, p.name);
	}
	
};

int main() {
	Person p1("kkk", 20);
	Person p2 = p1;	// 복사 생성자 호출 : 얕은 복사 - 컴파일러가 생성한 복사생성자, name은 복사하지 않음
	// 런타임 에러 : double free(미정의) - p2가 소멸자로 name을 삭제하기 때문에, p1이 dangling pointer가 됨.
	// 여기서 없는 메모리를 free하려 하니 segmentation fault.
	// 해결 : 깊은 복사
	getchar();
}
#endif

#if 1 // 3. 소유권 이전 방식
class Person {
	char* name;
	int age;
public:
	Person(const char* n, int a) : age(a) {
		name = new char[strlen(n) + 1];
		strcpy(name, n);
	}

	~Person() { delete[] name; }

	// 소유권 이전 정책의 복사 생성자
	Person(Person& p) : age(p.age), name(p.name) {	// 일단 얕은 복사 수행 후
		// 소유권 포기
		p.name = 0;
		p.age = 0;
	}
	// 언제 쓸까? swap 시에 깊은 복사를 3번이나 수행하면, 동적 할당을 여러번 해야 하니 성능상의 문제가 생김.
	// -> 소유권이전으로 하면 얕은 복사로 수행되니 성능이 좋게 swap이 됨
	// move constructor: 차세대 C++에서는 워낙 유명하니 아예 도입됨.
};

int main() {
	Person p1("kkk", 20);
	Person p2 = p1;
	// p1의 소멸자 불릴 때 문제 없나 ? 0번지(NULL)는 OS영역으로 지울 수 없고 넘어감. 안전함
	// 여기서 p1.name 하면? 죽는다. 해결 방법이 없다. 소유권 이전 복사라는 걸 알고 잘 써야 한다.
	getchar();
}
#endif
