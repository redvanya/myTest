// ��� �Լ��� �����ε�
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
	// const�� �����ε��� �����ϴ�. - �Ķ���Ͱ� �ٸ�
	void display() const { 	// void display(const Point* const this)
		printf("Point(%d, %d)\n", x, y);
		this = 0;		// ERROR
		this->x = 0;	// ERROR
	}
};

// ��� ��� �Լ��� �Ϲ� ��� �Լ��� �ñ״�ó�� �ٸ��Ƿ� �����ε� ����

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
	p.display();	// ��� �Լ� ȣ��: ��� ��ü�� ��� �Լ��� ȣ�� ����

	Point p2;
	p2.display();	// �⺻������ �Ϲ� �Լ� ȣ��, ���� �Ϲ� �Լ��� ������ ����å���� ����Լ� ȣ��
}