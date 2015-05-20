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

class Cursor : public Singleton<Cursor> {
	// �̱��� Ŭ������ ��ӹ޴� �ڽĿ��� �� ���� ��Ģ�� �߻�
	// Cursor() : Singleton() {}
	// 1. �ڽ��� Ŭ������ private���� �����ؾ� �մϴ�. -> �׷��� Cursor::getInstance() �� ������.. -> �׷��� ������� �̱��� ������ �� ����. ������� ����
	// 2. �θ� Ŭ������ ģ���� �ξ�� �մϴ�.
private:
	Cursor() {}
	friend class Singleton<Cursor>;
};

int main() {
	//Cursor c1;	// �⺻ �����ڰ� ȣ�� -> �ڽ��� Ŭ������ private���� ����
	//Cursor c2;	// ��� Error

	Cursor& c1 = Cursor::getInstance();		// ��� OK �ǵ��� �ؾ��� -> Cursor�� �⺻�����ڰ� private�̶� ���ø����� new TYPE�� �ȵ�.
	Cursor& c2 = Cursor::getInstance();		// �̱��� ���ø����� �� �� �ֵ��� friend ����

	cout << "&c1 = " << &c1 << endl;
	cout << "&c2 = " << &c2 << endl;
}

// 1. const_cast
// 2. mutable
// 3. friend
// -> ��¿ �� ���� ���� �͵�, �̰͵��� ���ٸ� ���谡 �߸��Ǿ����� �ɰ��ϰ� �����غ��� ��.

// Android Framework: ProcessState <-> IPCThread (binder) : ���� friend