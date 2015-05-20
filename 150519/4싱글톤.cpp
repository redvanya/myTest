// �����忡 ������ �̱��� (3.cpp ����)
#include <iostream>
using namespace std;

// ����ȭ ��ü�� �����մϴ�.
class Mutex {
public:
	void lock() { cout << "Mutex::lock()" << endl; }
	void unlock() { cout << "Mutex::unlock()" << endl; }
};

// RAII ��ü ����
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
			pInstance = new Cursor;	// new : heap�� �޸� �Ҵ� by OS, system�� memory�� �����ϸ� ���� �Ҵ� ���� -> ���� �߻� (C������ null ����)
									// ���� �߻� �� lock ������ �ȵ� -> RAII�� �ذ�
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