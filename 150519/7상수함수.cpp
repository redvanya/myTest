#include <iostream>
using namespace std;

class Point {
public:
	int x, y;
	Point(int a = 0, int b = 0) : x(a), y(b) {}
	void display() const {	// 객체의 상태의 안정성을 위하여 사용, display안쪽에서 값의 변경이 없도록 하기 위해
		printf("Point(%d, %d)\n", x, y);
		//x = 0;	// display는 보여주는 용도인데 값의 변화가 가능하다. 논리적으로 잘못됨 -> const 사용
	}
};

void display(const Point& p) {
	// const가 없으면 p에 대해 수정이 가능하다
	p.display();	// 컴파일러 입장에서 display에서 변경될 지도 모르니까 실행할 수 없다.
					// 이때 Point::display를 const로 변경하면 변경 안됨을 보장하기에 실행 가능. (상수객체는 상수함수만 호출 가능)
}

int main() {
	Point p(1, 1);
	display(p);	//p.display();
}

// 결론: 멤버를 변경하지 않는 멤버 함수의 경우에는 반드시 const 키워드를 붙이자!
// -> 상수 객체는 상수 함수만 호출할 수 있기 때문