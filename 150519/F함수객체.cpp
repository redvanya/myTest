#include <iostream>
#include <algorithm>	// for swap, sort
using namespace std;

#if 0
struct Less {
	inline bool operator()(int a, int b) {	return a > b; }
};

struct Greater {
	inline bool operator()(int a, int b) { return a < b; }
};

void Sort(int* arr, int len, Less compare) {
		for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (compare(arr[i], arr[j]))
				swap(arr[i], arr[j]);
		}
	}
}

void Sort(int* arr, int len, Greater compare) {
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (compare(arr[i], arr[j]))
				swap(arr[i], arr[j]);
		}
	}
}

void display(int* arr, int len) {
	for (int i = 0; i < len; i++) printf("%d ", arr[i]);
	getchar();
}

void main() {
	int arr[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	display(arr, 10);

	Less l;
	Sort(arr, 10, l);
	display(arr, 10);

	Greater g;
	Sort(arr, 10, g);
	display(arr, 10);
}
#endif

#if 0
struct Less {
	inline bool operator()(int a, int b) { return a > b; }
};

struct Greater {
	inline bool operator()(int a, int b) { return a < b; }
};

template <typename TYPE>	// 자칫 코드의 크기가 커질 수 있지만 성능 문제는 해결.
void Sort(int* arr, int len, TYPE compare) {
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (compare(arr[i], arr[j]))
				swap(arr[i], arr[j]);
		}
	}
}

void display(int* arr, int len) {
	for (int i = 0; i < len; i++) printf("%d ", arr[i]);
	getchar();
}

void main() {
	int arr[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	display(arr, 10);

	Less l;
	Sort(arr, 10, l);
	display(arr, 10);

	Greater g;
	Sort(arr, 10, g);
	display(arr, 10);
}
#endif

#include <functional>	// 함수 객체: greater, less

void display(int* arr, int len) {
	for (int i = 0; i < len; i++) printf("%d ", arr[i]);
	getchar();
}

bool asc_int(int a, int b) { return (a < b); }
bool des_int(int a, int b) { return (a > b); }

void main() {
	int arr[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, -1 };
	display(arr, 10);

	// 템플릿을 사용하면 성능상의 이슈는 없지만 : 컴파일러가 기계어 코드로 변환
	// 목적파일의 크기가 커져서 메모리가 많이 필요 : 타입에 비례하여 코드가 생성됨
	// 함수 객체를 사용할 경우
	// 장점: 성능이 좋아짐
	// 단점: 메모리 효율성이 떨어짐
	less<int> l;
	greater<int> g;

	sort(arr, arr + 10, l);	// sort(시작, 끝의 다음, 비교함수)
	display(arr, 10);
	sort(arr, arr + 10, g);
	display(arr, 10);

	// 그래서 STL 에서는 성능 vs 메모리를 선택 가능함. 템플릿도 사용할 수 있고, 함수 포인터도 사용 가능.
	// 함수 포인터를 사용할 경우
	// 장점: 메모리 최적화
	// 단점: 성능이 (상대적으로) 떨어짐
	sort(arr, arr + 10, asc_int);
	display(arr, 10);
	sort(arr, arr + 10, des_int);
	display(arr, 10);
}