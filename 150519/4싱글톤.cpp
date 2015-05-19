// 스레드에 안전한 싱글톤 (3.cpp 복사)
#include <iostream>
using namespace std;

// 동기화 객체를 설계합니다.
class Mutex {
public:
	void lock() { cout << "Mutex::lock()" << endl; }
	void unlock() { cout << "Mutex::unlock()" << endl; }
};

// RAII 객체 설계
class AutoLock {
	Mutex& mLock;

public:
	AutoLock(Mutex& m) : mLock(m) { m.lock(); }
	~AutoLock() { mLock.unlock(); }
};

class Cursor {
	Cursor(const Cursor&);					
	void operator=(const Cursor& c);		
	Cursor() {}

	static Mutex slock;
	static Cursor* pInstance;
public:
	static Cursor& getInstance() {
		AutoLock l(slock);
		//slock.lock();
		//----------------------------
		if (pInstance == 0)
			pInstance = new Cursor;	// new : heap에 메모리 할당 by OS, system에 memory가 부족하면 동적 할당 실패 -> 예외 발생 (C에서는 null 리턴)
									// 예외 발생 후 lock 해제가 안됨 -> RAII로 해결
		//----------------------------
		//slock.unlock();
		return *pInstance;
	}
};
Cursor* Cursor::pInstance = 0;
Mutex Cursor::slock;

int main() {
	Cursor& c = Cursor::getInstance();
}