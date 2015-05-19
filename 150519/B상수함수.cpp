// 상수 함수를 오버로딩 하는 이유
#include <iostream>
using namespace std;

class Vector {
	int* arr;
	int size;
public:
	Vector(int s = 5) : size(s) { arr = new int[s]; }
	~Vector() { delete[] arr; }

	int& operator [] (int i)	   { return arr[i]; }
	int  operator [] (int i) const { return arr[i]; }
};

int main() {
	Vector v;
	//v[0] = 1;	// v.operator[](0) = 0;
	cout << v[0] << endl;

	const Vector v1;
	cout << v1[0] << endl;
}