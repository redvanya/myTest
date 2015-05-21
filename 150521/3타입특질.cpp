// type traits
#include <iostream>
using namespace std;

#if 0
template<typename T> T Max(T a, T b) {
	if (T is pointer)	// 포인터 인지 아닌지 알 수 있는 방법이 없다 -> 만들어보자
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
// type traits: 타입 특질 또는 타입 특성
// 컴파일 타임에 타입의 특성이나 또는 특질을 알아내는 기술

// 주 템플릿은 거짓을 반환
// 부분 전문화는 참을 반환
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

#if 0 // 연습문제

template<typename T> struct my_is_array {
	enum { value = false, size = -1 };
};
// void foo에서 &레퍼런스로 받았기 때문에 이는 C++의 타입이라서 decay 일어나지 않는다.
// int a[1]이라면 int[1] 타입인 것.
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

// type traits 기술은 이미 표준에서 지원하고 있다
int *p;
int arr[3];

int main() {
	if (is_pointer<int*>::value)	cout << "pointer" << endl;
	if (is_array<int[3]>::value)	cout << "array" << endl;
}