#include <iostream>
using namespace std;

#if 0
class Car {
	int mCount;
public:
	// ���� ����� �����ϱ� ���� �������̽� ����
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
	Car* p1 = new Car;	// ��ü ���� ��, ���� ��� ����
	p1->incStrong();

	Car* p2 = p1;	// ��ü ���� ��, ���� ��� ����
	p2->incStrong();

	// ��ü�� ����� ���� ��� (���� �ΰ��� ��� ��)
	p2->decStrong();
	p1->decStrong();	// ���� ��� ����
	// ���� ��� ���� ��, �Ҹ�
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

// �ڵ���, Ʈ��, �ýõ� mCount�� �� �������̽��� ������ �־�� ��.
// �Ź� ������ �����ϱ� �����ϴ� -> ��������� �ڵ�ȭ
class Car {
	int mCount;
public:
	// ���� ����� �����ϱ� ���� �������̽� ����
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

// ���� ����� ���õ� �ڵ带 �ڵ����� ������ �� �ֵ��� �θ� Ŭ���� ����
class RefBase {
	int mCount;
public:
	RefBase() : mCount(0) {}
	void incStrong() { ++mCount; }
	void decStrong() {
		if ( --mCount == 0)
			delete this;
	}
	virtual ~RefBase() {}	// �ڽ��� �Ҹ��ڰ� �Ҹ����� �ϱ� ���ؼ� �ݵ�� virtual�� �����.
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

// RefBase�� ��� ���� �� ��� �̹� �Ǿ� ����
//			RefBase
//		  /			\
//   IBinder      IInterface
//		  \		   /
//        LedService