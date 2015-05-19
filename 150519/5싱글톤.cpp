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

class Cursor: public Singleton<Cursor> {};

int main() {
	Cursor& c1 = Cursor::getInstance();	// Singleton에서 자식의 symbol을 받아야 함 -> CRTP
	Cursor& c2 = Cursor::getInstance();

	cout << "&c1 = " << &c1 << endl;
	cout << "&c2 = " << &c2 << endl;
}