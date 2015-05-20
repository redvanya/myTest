// 상속
#include <iostream>
using namespace std;

class Mutex {
public:
	void lock() { cout << "Mutex::lock()" << endl; }
	void unlock() { cout << "Mutex::unlock()" << endl; }
};

class AutoLock {
	Mutex& mLock;

public:
	AutoLock(Mutex& m) : mLock(m) { m.lock(); }
	~AutoLock() { mLock.unlock(); }
};

template<typename TYPE>
class Singleton {
protected:	// 자식은 생성자를 호출할 수 있도록 하기 위해 protected
	Singleton() {}
private:
	Singleton(const TYPE&);
	void operator=(const TYPE&);

	static Mutex slock;
	static TYPE* pInstance;
public:
	static TYPE& getInstance() {
		AutoLock l(slock);
		if (pInstance == 0)
			pInstance = new TYPE;
		return *pInstance;
	}
};
template<typename TYPE> Mutex Singleton<TYPE>::slock;
template<typename TYPE> TYPE* Singleton<TYPE>::pInstance = 0;

// 위의 코드는 프레임워크가 제공하는 코드입니다.
//-------------------------------------------------------------
// 아래의 코드는 사용자가 구현하는 코드입니다.

class Cursor : public Singleton<Cursor> {
	// 싱글톤 클래스를 상속받는 자식에게 한 가지 규칙이 발생
	// Cursor() : Singleton() {}
	// 1. 자식의 클래스를 private으로 정의해야 합니다. -> 그러면 Cursor::getInstance() 가 에러남.. -> 그래서 상속으로 싱글톤 구현을 잘 안함. 깔끔하지 못함
	// 2. 부모 클래스와 친구를 맺어야 합니다.
private:
	Cursor() {}
	friend class Singleton<Cursor>;
};

int main() {
	//Cursor c1;	// 기본 생성자가 호출 -> 자식의 클래스를 private으로 정의
	//Cursor c2;	// 얘는 Error

	Cursor& c1 = Cursor::getInstance();		// 얘는 OK 되도록 해야함 -> Cursor의 기본생성자가 private이라 템플릿에서 new TYPE이 안됨.
	Cursor& c2 = Cursor::getInstance();		// 싱글톤 템플릿에서 쓸 수 있도록 friend 선언

	cout << "&c1 = " << &c1 << endl;
	cout << "&c2 = " << &c2 << endl;
}

// 1. const_cast
// 2. mutable
// 3. friend
// -> 어쩔 수 없이 쓰는 것들, 이것들을 쓴다면 설계가 잘못되었는지 심각하게 고찰해봐야 함.

// Android Framework: ProcessState <-> IPCThread (binder) : 둘은 friend