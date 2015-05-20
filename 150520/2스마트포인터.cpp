#include <iostream>
using namespace std;

#if 0
class Car {
public:
	Car() { cout << "Car()" << endl; }
	~Car() { cout << "~Car()" << endl; }

	void go() { cout << "go! go! go!" << endl; }
};

void main() {
	{
		// 힙 객체의 소멸자가 호출되는 시점은 delete 연산자를 사용
		// 즉, delete 연산을 하지 않을 경우 객체는 여전히 힙에 존재
		// -> 메모리 누수 현상 (memory leak)
		Car* pCar = new Car;	// 힙에 생성된 객체는 명시적으로 소멸자를 불러줘야 한다.
		// delete pCar;
		// 메모리 누수 발생
	}
	getchar();
}

//void main() {
//	// 스택 프레임 생성
//	{
//		Car c;	// 지역 객체 and 자동 변수
//				// 지역 객체는 메모리가 자동으로 생성되고 생성자가 호출된다
//				// 지역 객체의 소멸자는 객체가 스택에서 파괴될 때 호출
//	}
//	getchar();
//}
#endif

#if 0
class Car {
public:
	Car() { cout << "Car()" << endl; }
	~Car() { cout << "~Car()" << endl; }

	void go() { cout << "go! go! go!" << endl; }
};

// 자원 관리를 위한 클래스를 도입해봅시다 : 소멸자를 활용한 자원의 해지
// 객체가 포인터 역할을 하는 것을 스마트포인터라 한다
class Sptr {
	Car* pObj;
public:
	Sptr(Car* p) : pObj(p) {}
	~Sptr() { delete pObj; }

	Car* operator->() { return pObj; }
	Car& operator*() { return *pObj; }	// Car를 리턴하면 임시객체가 생성되어 소멸자가 두번 불림. 참조자로 리턴하기
};

void main() {
	{
		//Car* pCar = new Car;	// 소멸자 안불림
		Sptr pCar = new Car;	// 소멸자 불림
		pCar->go();		// garbage collector는 동작하지만 실제 포인터처럼 동작하지 않는다 -> 연산자 오버로딩 "->" 필요
						// pCar.operator->()go(); : 컴파일 에러 -> (pCar.operator->())->go(); 포인터 리턴
		(*pCar).go();		// pCar.operator*().go(); 연산자 우선순위가 . > * 이기 때문에 ()로 묶어준다
	}
	getchar();
}
#endif

class Car {
public:
	Car() { cout << "Car()" << endl; }
	~Car() { cout << "~Car()" << endl; }

	void go() { cout << "go! go! go!" << endl; }
};

// 스마트 포인터란 임의의 객체가 다른 타입의 포인터 역할을 하는것
template <typename T>
class Sptr {
	T* pObj;
public:
	Sptr(T* p) : pObj(p) {}
	~Sptr() { delete pObj; }

	// 스마트 포인터는 아래의 두 연산자를 재정의 해야한다
	T* operator->() { return pObj; }
	T& operator*() { return *pObj; }
};

// 스마트 포인터는 진짜 포인터가 아닌 객체이므로 사용자가 객체의 생성/복사/대입/소멸의 과정을 제어할 수 있다.
// 대표적인 활용 예) 소멸자를 사용한 자동 삭제
void main() {
	{
		Sptr<Car> pCar = new Car;
		pCar->go();
		(*pCar).go();
	}
	getchar();
}