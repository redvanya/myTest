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

	Sptr(const Sptr& o) : pObj(o.pObj), ref(o.ref) {	// ���� ���� ���
		++(*ref);
	}

	T* operator->() { return pObj; }
	T& operator*() { return *pObj; }
};

void main()
{
	//{
	//	int* p1 = new int;
	//	*p1 = 10;
	//	cout << *p1 << endl;

	//	getchar();

	//	int* p2 = p1;
	//	*p2 = 20;
	//	cout << *p1 << endl;
	//}
	{
		Sptr<int> p1 = new int;
		*p1 = 20;
		cout << *p1 << endl;

		getchar();

		Sptr<int> p2 = p1;
		*p2 = 0;
		cout << *p1 << endl;
		
		getchar();	// ����Ʈ �����Ϳ� ��������ڰ� ���ǵǾ� ���� �ʾƼ� double free�� �Ͼ�� ��Ÿ�ӿ���
					// ���� ����� �����ϸ� �����ÿ� ������ ������, ��¥ �����Ϳʹ� �޸� ������ �ٸ���. p2���� ���� �����ص� p1���� ������� ����
					// -> ������� ����ϱ�
	}
}
#endif

// ����Ʈ �������� ����: �޸𸮰� �ι� -> �׷��� �� ��� �� ��.
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

void main()
{
	cout << sizeof(int*) << endl;		// 4byte
	cout << sizeof(Sptr<int>) << endl;	// 8byte
}