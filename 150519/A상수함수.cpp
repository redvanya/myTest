// 상수 함수의 오버로딩
#include <iostream>
using namespace std;

#if 0
class Point {
public:
	int x, y;
	Point(int a = 0, int b = 0) : x(a), y(b) {}

	void display()	// void display(Point* const this)
	{ 
		printf("Point(%d, %d)\n", x, y);
		this = 0;		// ERROR
		this->x = 0;	// OK
	}
	// const도 오버로딩이 가능하다. - 파라미터가 다름
	void display() const { 	// void display(const Point* const this)
		printf("Point(%d, %d)\n", x, y);
		this = 0;		// ERROR
		this->x = 0;	// ERROR
	}
};

// 상수 멤버 함수와 일반 멤버 함수는 시그니처가 다르므로 오버로딩 가능

void main() {
	Point p;
	p.display();
}
#endif

class Point {
public:
	int x, y;
	Point(int a = 0, int b = 0) : x(a), y(b) {}

	//void display() { printf("called Point()\n"); }
	void display() const { printf("called Point() const\n"); }
};

void main() {
	const Point p;
	p.display();	// 상수 함수 호출: 상수 객체는 상수 함수만 호출 가능

	Point p2;
	p2.display();	// 기본적으로 일반 함수 호출, 만약 일반 함수가 없으면 차선책으로 상수함수 호출
}