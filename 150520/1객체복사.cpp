// 객체 복사 정책
// 1. 얕은 복사 (shallow copy)	 : C++기본 정책으로, 동적할당된 객체는 복사가 되지 않는다.
//								   따라서 포인터를 가지고는 유효한 객체인지 알 수 없기 때문에 double free가 발생
// 2. 깊은 복사					 : 동적 할당 객체가 복사되지만, new 연산 비용이 크고 사본이 생겨서 메모리가 낭비된다. 따라서 학문적으로만 쓰고 실제로 사용은 하지 않음.
// 3. 복사 금지 (Unique_ptr)		 : 복사생성자를 private으로 놓기
// 4. *소유권 이전 정책 (auto_ptr) : 쓸모가 없는 것처럼 보이지만, 객체의 swap시에 메모리 오버헤드를 줄여준다.
//								   이것이 매우 좋아서 차세대 C++에서는 아예 이동 생성자로 문법의 도입이 됨.
// 5. *참조 계수 기반 (share_ptr)	 : 얕은 복사 -> 카운팅 하고 있는 것이 없으면 삭제

// 5. 참조 계수 기반의 복사 정책
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
	
	// 참조 계수 기반의 복사 정책
	Person(const Person& o) : name(o.name), age(o.age), ref(o.ref) {	// 얕은 복사 기반
		// 참조 계수 증분
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