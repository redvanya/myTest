// 인라인과 성능
#include <iostream>
#include <algorithm>	// for swap
using namespace std;

#if 0
// 오름 차순
void ASort(int* arr, int len) {
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (arr[i] > arr[j])
				swap(arr[i], arr[j]);
		}
	}
}

// 내림 차순
void DSort(int* arr, int len) {
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (arr[i] < arr[j])
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
	ASort(arr, 10);
	display(arr, 10);
	DSort(arr, 10);
	display(arr, 10);
}
#endif

#if 1
void Sort(int* arr, int len, bool(*compare)(int, int)) {	// 함수포인터 이용 - 인라인함수로 못쓰고, 런타임시 알 수 있기 때문에 라이브러리 성능 저하.
															// 비슷한 예로 quick sort를 잘 사용하지 않음
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (compare(arr[i], arr[j]))	// if(arr[i] > arr[j])
				swap(arr[i], arr[j]);
		}
	}
}

inline bool asc_int(int a, int b) { return (a > b); }
inline bool des_int(int a, int b) { return (a < b); }

void display(int* arr, int len) {
	for (int i = 0; i < len; i++) printf("%d ", arr[i]);
	getchar();
}

void main() {
	int arr[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	display(arr, 10);
	Sort(arr, 10, asc_int);
	display(arr, 10);
	Sort(arr, 10, des_int);
	display(arr, 10);
}
#endif
