// type traits
#include <iostream>
using namespace std;

#if 0
template<typename T> T Max(T a, T b) {
	if (T is pointer)	// ������ ���� �ƴ��� �� �� �ִ� ����� ���� -> ������
		return *a > *b ? *a : *b;
	else
		return a > b ? a : b;	
}

int main() {
	int a = 10, b = 20;
	cout << Max(a, b) << endl;
}
#endif

#if 0
// type traits: Ÿ�� Ư�� �Ǵ� Ÿ�� Ư��
// ������ Ÿ�ӿ� Ÿ���� Ư���̳� �Ǵ� Ư���� �˾Ƴ��� ���

// �� ���ø��� ������ ��ȯ
// �κ� ����ȭ�� ���� ��ȯ
template<typename T> struct my_is_pointer {
	enum { value = false };
};

template<typename T> struct my_is_pointer<T*> {
	enum { value = true };
};

template<typename T> void foo(const T& a) {
	if (my_is_pointer<T>::value)
		cout << "pointer" << endl;
	else
		cout << "no pointer" << endl;
}

void main() {
	int i;
	foo(i);	// no pointer
	int* p;
	foo(p);	// pointer
}
#endif

#if 0 // ��������

template<typename T> struct my_is_array {
	enum { value = false, size = -1 };
};
// void foo���� &���۷����� �޾ұ� ������ �̴� C++�� Ÿ���̶� decay �Ͼ�� �ʴ´�.
// int a[1]�̶�� int[1] Ÿ���� ��.
template<typename T, int N> struct my_is_array < T[N] > {
	enum { value = true, size = N };
};

template<typename T> void foo(const T& a) {
	if (my_is_array<T>::value)
		cout << "array size = " << my_is_array<T>::size << endl;
	else
		cout << "no array" << endl;
};

int main() {
	int i;
	foo(i);		// no array
	int a[8];
	foo(a);		// array
}
#endif

// type traits ����� �̹� ǥ�ؿ��� �����ϰ� �ִ�
int *p;
int arr[3];

int main() {
	if (is_pointer<int*>::value)	cout << "pointer" << endl;
	if (is_array<int[3]>::value)	cout << "array" << endl;
}