// ���
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
protected:	// �ڽ��� �����ڸ� ȣ���� �� �ֵ��� �ϱ� ���� protected
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

// ���� �ڵ�� �����ӿ�ũ�� �����ϴ� �ڵ��Դϴ�.
//-------------------------------------------------------------
// �Ʒ��� �ڵ�� ����ڰ� �����ϴ� �ڵ��Դϴ�.

class Cursor: public Singleton<Cursor> {};

int main() {
	Cursor& c1 = Cursor::getInstance();	// Singleton���� �ڽ��� symbol�� �޾ƾ� �� -> CRTP
	Cursor& c2 = Cursor::getInstance();

	cout << "&c1 = " << &c1 << endl;
	cout << "&c2 = " << &c2 << endl;
}