// ��� �Լ��� ����
#include <iostream>
using namespace std;

class Point {
public:
	int x, y;
	mutable char str[32];	// ��� �Լ� ���ʿ��� ��¿ �� ���� �����ؾ� �Ѵٸ� mutable Ű����
	mutable bool cached;	// const_cast, mutable�� 80~90% �߸��� ����. �� ���°� ����

	Point(int a = 0, int b = 0) : x(a), y(b), cached(false) {}

	// ���� ��ü�� ���ڿ��� �����ϱ� ���� to_str �Լ�
	const char* to_str() const{	// char* to_str(Const Point* const this)
		if (cached == false) {
			sprintf(str, "Point(%d, %d)", x, y);
			cached = true;
		}
		return str;
	}
	// ��� �Լ��� ��� ������ �����ͳ� ������ ��ȯ�� �� �����ϴ�. -> const�� ����
};

int main() {
	Point p(1, 1);
	cout << p.to_str() << endl;
}