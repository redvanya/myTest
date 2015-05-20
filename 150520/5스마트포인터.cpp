// 참조 계수 기반의 스마트 포인터는 이미 표준에서 지원한다
#include <iostream>
#include <memory>
using namespace std;

template<typename T> class android_sp {
	T* pObj;
public:
	Sptr(T* p) : pObj(p) { if (pObj) pObj->incStrong(); }
	~Sptr() { if (pObj) pObj->decStrong(); }
	Sptr(const Sptr& o) : pObj(o.pObj) { if (pObj) pObj->incStrong(); }

	T* operator->() { return pObj; }
	T& operator*() { return *pObj; }
};

int main() {
	shared_ptr<int> p1(new int);	// shared_ptr<int> p1 = shared_ptr<int>(new int);
	*p1 = 20;
	cout << *p1 << endl;
	shared_ptr<int> p2(p1);
	cout << sizeof(shared_ptr<int>) << endl;	// 메모리 2배: 8 -> 안드로이드의 스마트포인터는 4, 하지만 단점이 있다

	android_sp<int> p3 = new int;	// Error: int는 builtin타입으로, RefBase 멤버함수가 없기 때문에 안된다.
									// 메모리를 얻은 대신 범용타입에 대한 관리를 버림
}

// shared_ptr의 장점: 모든 타입 처리 가능
//				단점: 메모리 낭비 (일반 포인터의 2배)

// android_sp의 장점: 메모리의 낭비 없음
//				단점: RefBase의 서브 클래스만 관리될 수 있다. (기본 타입은 안됨)