// 상수 함수의 문제
#include <iostream>
using namespace std;

class Point {
public:
	int x, y;
	mutable char str[32];	// 상수 함수 안쪽에서 어쩔 수 없이 변경해야 한다면 mutable 키워드
	mutable bool cached;	// const_cast, mutable은 80~90% 잘못된 설계. 안 쓰는게 좋다

	Point(int a = 0, int b = 0) : x(a), y(b), cached(false) {}

	// 현재 객체를 문자열로 변경하기 위한 to_str 함수
	const char* to_str() const{	// char* to_str(Const Point* const this)
		if (cached == false) {
			sprintf(str, "Point(%d, %d)", x, y);
			cached = true;
		}
		return str;
	}
	// 상수 함수는 멤버 변수의 포인터나 참조를 반환할 수 없습니다. -> const로 리턴
};

int main() {
	Point p(1, 1);
	cout << p.to_str() << endl;
}