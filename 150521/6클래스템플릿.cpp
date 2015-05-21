#include <iostream>
using namespace std;

#if 0
template<typename T>
class Sptr {
	T* pObj;
	int* ref;
public:
	Sptr(T* p) : pObj(p), ref(new int(1)) {}
	~Sptr() {
		if (--(*ref) == 0) {
			delete pObj;
			delete ref;
		}
	}

	Sptr(const Sptr& o) : pObj(o.pObj), ref(o.ref) {
		++(*ref);
	}

	T* operator->() { return pObj; }
	T& operator*() { return *pObj; }
};

class Animal {};
class Dog : public Animal {};

void main(){
	Animal* p1 = new Dog;		// OK
	Sptr<Animal> p2 = new Dog;	// OK

	Dog* p3 = new Dog;
	Animal* p4 = p3;	// 진짜 포인터는 Animal에 Dog 타입 포인터 대입 가능
	Sptr<Dog> p5 = new Dog;
	Sptr<Animal> p6 = p5;	// 스마트포인터는 안된다.
}
#endif

template<typename T>
class Sptr {
	T* pObj;
	int* ref;
	/*template<typename U>*/ friend class Sptr;
public:
	Sptr(T* p) : pObj(p), ref(new int(1)) {}
	~Sptr() {
		if (--(*ref) == 0) {
			delete pObj;
			delete ref;
		}
	}
	
	Sptr(const Sptr& o) : pObj(o.pObj), ref(o.ref) {
		++(*ref);
	}

	template<typename U>	// 멤버 함수 템플릿이 없으면 상속관계에서의 upcasting이 안된다. 꼭 필요함
	Sptr(const Sptr<U>& o) : pObj(o.pObj), ref(o.ref) {
		++(*ref);
	}
	
	T* operator->() { return pObj; }
	T& operator*() { return *pObj; }
};

class Animal {};
class Dog : public Animal {};

void main(){
	Dog* p3 = new Dog;
	Animal* p4 = p3;
	Sptr<Dog> p5 = new Dog;
	Sptr<Animal> p6 = p5;
}