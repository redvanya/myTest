// ���� ��� ����� ����Ʈ �����ʹ� �̹� ǥ�ؿ��� �����Ѵ�
#include <iostream>
#include <memory>
using namespace std;

template<typename T> class android_sp {
	T* pObj;
public:
	Sptr(T* p) : pObj(p) { if (pObj) pObj->incStrong(); }
	~Sptr() { if (pObj) pObj->decStrong(); }
	Sptr(const Sptr& o) : pObj(o.pObj) { if (pObj) pObj->incStrong(); }

	T* operator->() { return pObj; }
	T& operator*() { return *pObj; }
};

int main() {
	shared_ptr<int> p1(new int);	// shared_ptr<int> p1 = shared_ptr<int>(new int);
	*p1 = 20;
	cout << *p1 << endl;
	shared_ptr<int> p2(p1);
	cout << sizeof(shared_ptr<int>) << endl;	// �޸� 2��: 8 -> �ȵ���̵��� ����Ʈ�����ʹ� 4, ������ ������ �ִ�

	android_sp<int> p3 = new int;	// Error: int�� builtinŸ������, RefBase ����Լ��� ���� ������ �ȵȴ�.
									// �޸𸮸� ���� ��� ����Ÿ�Կ� ���� ������ ����
}

// shared_ptr�� ����: ��� Ÿ�� ó�� ����
//				����: �޸� ���� (�Ϲ� �������� 2��)

// android_sp�� ����: �޸��� ���� ����
//				����: RefBase�� ���� Ŭ������ ������ �� �ִ�. (�⺻ Ÿ���� �ȵ�)