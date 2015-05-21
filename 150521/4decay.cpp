#include <iostream>
using namespace std;

#if 0
void init_int(int a)	{ a = 0; }
void init_arr(int a[])	{ a[0] = 0; }

void main() {
	int i = 10;
	int a[10] = { 20 };

	init_int(i);	// init_int(10); -> 안변함. call by value
	cout << i << endl;

	// 포인터 변수의 선언 : 대상체의 타입 * 변수명;
	int* pInt = &i;

	getchar();

	init_arr(a);	// init_ar(0x12FF60); -> 0으로 초기화됨. array는 pointer로 변경되어 넘어감.
	cout << a[0] << endl;

	//int(* pArr)[1] = a;	// 원래 a는 int[1] 타입이지만 아래처럼 int의 포인터타입, 즉 첫번째 (a[0])의 포인터 타입으로 축소된다.
	int* pArr = a;	// decay: 배열의 타입이 배열 전체에서 첫 번째 원소의 타입으로 축소 또는 퇴화
	cout << sizeof a << endl;	// 배열에서 유일하게 decay가 발생하지 않는 것은 sizeof 연산자
}
#endif

#if 0
// Argument Decay: 템플릿에도 디케이발생

// (T)을 인자로 받을 경우: 배열과 함수는 decay가 발생한다
template<typename T> void type_check_val(T t) {
	cout << typeid(t).name() << endl;
}

// 참조(&T)를 인자로 받을 경우: 정확한 배열의 타입으로 전달됨
template<typename T> void type_check_ref(T& t) {
	cout << typeid(t).name() << endl;
}

void main() {
	int i = 0;
	type_check_val(i);	// int가 나온다
	type_check_ref(i);	// int가 나온다

	int arr[3];
	type_check_val(arr);	// int * 이 나온다 - 전통적인 C의 문법에 따라 전체 배열의 첫번째 원소의 포인터 타입으로 전달되는 decay가 발생한다.
	type_check_ref(arr);	// int [3] 가 나온다 - 정확한 배열의 타입

	type_check_val("hello");	// char const *
	type_check_ref("hello");	// char const [6]

	type_check_val(main);	// 함수 포인터: int (__cdecl*)(void)
	type_check_ref(main);	// 일반 함수 그대로 나옴: int __cdecl(void)
}
#endif

// 연습문제
template<typename T> void foo(T a, T b) {
	cout << "called foo(T)" << endl;
}

template<typename T> void goo(T& a, T& b) {
	cout << "called goo(T&)" << endl;
}

void goo(const char* a, const char* b) {
	cout << "called goo(char*)" << endl;
}

// 컴파일러가 일반 함수와 함수 템플릿이 오버로딩 된 경우, 찾는 순서
// 일반 함수 -> 함수 템플릿

void main() {
	foo("kk", "hhhh");	// void foo(const char*, const char*);


	goo("kkk", "hhh");	// void goo(const char[3], const char[3]) -> 두 배열의 길이가 같아서 T&로 받을 수 있다
	goo("kkkasdfasdf", "hhhhasdfasfd");	// 두 파라미터의 길이가 달라서 다른 타입으로 인식. 템플릿 쓸 수 없다 -> 일반 함수 오버로딩
}