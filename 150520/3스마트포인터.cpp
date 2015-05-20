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

	Sptr(const Sptr& o) : pObj(o.pObj), ref(o.ref) {	// 얕은 복사 기반
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
		
		getchar();	// 스마트 포인터에 복사생성자가 정의되어 있지 않아서 double free가 일어나서 런타임에러
					// 깊은 복사로 변경하면 삭제시엔 문제가 없지만, 진짜 포인터와는 메모리 구조가 다르다. p2에서 값을 변경해도 p1에서 변경되지 않음
					// -> 참조계수 사용하기
	}
}
#endif

// 스마트 포인터의 단점: 메모리가 두배 -> 그래서 잘 사용 안 함.
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