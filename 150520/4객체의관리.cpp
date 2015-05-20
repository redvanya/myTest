#include <iostream>
using namespace std;

#if 0
class Car {
	int mCount;
public:
	// 참조 계수를 관리하기 위한 인터페이스 제공
	void incStrong() { ++mCount; }
	void decStrong() {
		--mCount;
		if (mCount == 0)
			delete this;
	}

	Car() : mCount(0) { cout << "Car()" << endl; }
	~Car() { cout << "~Car()" << endl; }
	void go() { cout << "go!" << endl; }

};

void main() {
	Car* p1 = new Car;	// 객체 생성 후, 참조 계수 증가
	p1->incStrong();

	Car* p2 = p1;	// 객체 복사 후, 참조 계수 증가
	p2->incStrong();

	// 객체의 사용이 끝난 경우 (현재 두개가 사용 중)
	p2->decStrong();
	p1->decStrong();	// 참조 계수 감소
	// 참조 계수 감소 후, 소멸
}
#endif

#if 0
template<typename T>
class Sptr {
	T* pObj;
public:
	Sptr(T* p) : pObj(p) { if (pObj) pObj->incStrong(); }
	~Sptr() { if (pObj) pObj->decStrong(); }
	Sptr(const Sptr& o) : pObj(o.pObj) { if (pObj) pObj->incStrong(); }

	T* operator->() { return pObj; }
	T& operator*() { return *pObj; }
};

// 자동차, 트럭, 택시도 mCount와 그 인터페이스를 가지고 있어야 함.
// 매번 유저가 구현하기 불편하다 -> 참조계수도 자동화
class Car {
	int mCount;
public:
	// 참조 계수를 관리하기 위한 인터페이스 제공
	void incStrong() { ++mCount; }
	void decStrong() {
		if (--mCount == 0)
			delete this;
	}

	Car() : mCount(0) { cout << "Car()" << endl; }
	~Car() { cout << "~Car()" << endl; }
	void go() { cout << "go!" << endl; }

};
void main() {
	Sptr<Car> p1 = new Car;
	Sptr<Car> p2 = p1;

	cout << sizeof Sptr<Car> << endl;
}
#endif 

template<typename T>
class Sptr {
	T* pObj;
public:
	Sptr(T* p) : pObj(p) { if (pObj) pObj->incStrong(); }
	~Sptr() { if (pObj) pObj->decStrong(); }
	Sptr(const Sptr& o) : pObj(o.pObj) { if (pObj) pObj->incStrong(); }

	T* operator->() { return pObj; }
	T& operator*() { return *pObj; }
};

// 참조 계수와 관련된 코드를 자동으로 생성할 수 있도록 부모 클래스 설계
class RefBase {
	int mCount;
public:
	RefBase() : mCount(0) {}
	void incStrong() { ++mCount; }
	void decStrong() {
		if ( --mCount == 0)
			delete this;
	}
	virtual ~RefBase() {}	// 자식의 소멸자가 불리도록 하기 위해서 반드시 virtual로 써야함.
};

class Car : public RefBase {
public:
	Car() { cout << "Car()" << endl; }
	~Car() { cout << "~Car()" << endl; }
	void go() { cout << "go!" << endl; }

};
void main() {
	Sptr<Car> p1 = new Car;
	Sptr<Car> p2 = p1;

	cout << sizeof Sptr<Car> << endl;
}

// RefBase를 상속 받은 적 없어도 이미 되어 있음
//			RefBase
//		  /			\
//   IBinder      IInterface
//		  \		   /
//        LedService