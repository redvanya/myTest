#include <iostream>
#include <cstdlib>
using namespace std;

#if 0
class Point {
public:
	Point() { cout << "Point()" << endl; }
	~Point() { cout << "~Point()" << endl; }
};

void main() {
	Point* p = static_cast<Point*>(operator new(sizeof(Point)));	// 생성자가 호출되지 않는다 -> operator new()는 함수?!
	cout << p << endl;
}

// new 연산자가 하는일
// 1. 메모리 동적 할당. 실패한다면 null 리턴
// 2. 동적 할당에 성공하고 피연산자가 사용자 정의 타입이라면 생성자 호출
// 3. lvalue 타입으로 형 변환

//void main() {
//	Point* p1 = static_cast<Point*>(malloc(sizeof(Point)));	// 생성자가 호출되지 않는다
//	Point* p2 = new Point;	// 생성자가 호출된다
//}
#endif

#if 0
// new 연산자의 실제 모양
// new 연산자의 첫 번째 인자는 무조건 size
void* operator new(size_t size){
	cout << "new(size_t)" << endl;
	return malloc(size);
}

void* operator new(size_t size, const char* fname){
	cout << "new : " << fname << endl;
	return malloc(size);
}

void* operator new(size_t size, const char* fname, int line){
	cout << "new : " << fname << " - " << line << endl;
	return malloc(size);
}

void main() {
	// 디버깅이 제공되지 않는다면 오버로딩 해서 쓸 수 있다
	int* p1 = new int;	// 피연산자의 크기를 어떻게 얻어올까? (보통은 sizeof를 쓴다) -> 여기서 new 연산자에는 피연산자의 크기를 나타내는 인자가 하나 있다고 추론 가능
	int* p2 = new("이렇게") int;	// 첫 번째 인자는 오른쪽에 쓰도록 했지만 오버로딩한 함수의 두번째 인자를 쓰기 위해서는 이런 식으로 써야 함.
	int* p3 = new(__FILE__, __LINE__) int;
}
#endif

#if 0
class Point {
public:
	Point() { cout << "Point()" << endl; }
	~Point() { cout << "~Point()" << endl; }
};

// 이미 표준에서 void* operator new(size_t, void*)을 제공하고 있다 -> 명시적 생성자 호출이 필요하니까
//void* operator new(size_t size, void* p){
//	return p;
//}

void main() {
	Point* p = static_cast<Point*>(malloc(sizeof(Point)));
	new(p) Point;	// new에서 생성자를 호출해주니까 new를 오버로딩한 함수로 명시적으로 생성자 호출 가능
}

//void main() {
//	Point p;
//	p.~Point();	// 소멸자는 명시적으로 호출 가능 - main이 끝나지 않아 아직 지역객체가 삭제되지 않았지만 소멸자 호출 가능
//	p.Point();	// 생성자는 안된다 -> 메모리만 할당 후 명시적으로 부를 수 있다?
//}
#endif

// 생성자의 명시적 호출이 필요한 경우 : Placement New
class Point {
public:
	Point(int a, int b) { cout << "Point(" << a << " ," << b << ")" << endl; }
};

void main() {
	//Point* p1 = new Point(0, 0);	// 정상적으로 객체 할당
	//Point* p2 = new Point[10];	// Point에 기본생성자가 없는 상태에서 배열로 만들고 싶으면?
	Point* p2 = static_cast<Point*>(malloc(10 * sizeof(Point)));	// 1. 먼저 생성자 없이 메모리 할당
	for (int i = 0; i < 10; i++)	// 2. 10개의 객체에 각각 생성자 호출
		new(p2 + i) Point(0, 0);	//new(&p2[i]) Point(0, 0);
}
