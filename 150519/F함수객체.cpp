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

template <typename TYPE>	// ��ĩ �ڵ��� ũ�Ⱑ Ŀ�� �� ������ ���� ������ �ذ�.
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

#include <functional>	// �Լ� ��ü: greater, less

void display(int* arr, int len) {
	for (int i = 0; i < len; i++) printf("%d ", arr[i]);
	getchar();
}

bool asc_int(int a, int b) { return (a < b); }
bool des_int(int a, int b) { return (a > b); }

void main() {
	int arr[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, -1 };
	display(arr, 10);

	// ���ø��� ����ϸ� ���ɻ��� �̽��� ������ : �����Ϸ��� ���� �ڵ�� ��ȯ
	// ���������� ũ�Ⱑ Ŀ���� �޸𸮰� ���� �ʿ� : Ÿ�Կ� ����Ͽ� �ڵ尡 ������
	// �Լ� ��ü�� ����� ���
	// ����: ������ ������
	// ����: �޸� ȿ������ ������
	less<int> l;
	greater<int> g;

	sort(arr, arr + 10, l);	// sort(����, ���� ����, ���Լ�)
	display(arr, 10);
	sort(arr, arr + 10, g);
	display(arr, 10);

	// �׷��� STL ������ ���� vs �޸𸮸� ���� ������. ���ø��� ����� �� �ְ�, �Լ� �����͵� ��� ����.
	// �Լ� �����͸� ����� ���
	// ����: �޸� ����ȭ
	// ����: ������ (���������) ������
	sort(arr, arr + 10, asc_int);
	display(arr, 10);
	sort(arr, arr + 10, des_int);
	display(arr, 10);
}