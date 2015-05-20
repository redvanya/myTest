#include <iostream>
using namespace std;

class Point {
public:
	int x, y;
	Point(int a = 0, int b = 0) : x(a), y(b) {}
	void display() const {	// ��ü�� ������ �������� ���Ͽ� ���, display���ʿ��� ���� ������ ������ �ϱ� ����
		printf("Point(%d, %d)\n", x, y);
		//x = 0;	// display�� �����ִ� �뵵�ε� ���� ��ȭ�� �����ϴ�. �������� �߸��� -> const ���
	}
};

void display(const Point& p) {
	// const�� ������ p�� ���� ������ �����ϴ�
	p.display();	// �����Ϸ� ���忡�� display���� ����� ���� �𸣴ϱ� ������ �� ����.
					// �̶� Point::display�� const�� �����ϸ� ���� �ȵ��� �����ϱ⿡ ���� ����. (�����ü�� ����Լ��� ȣ�� ����)
}

int main() {
	Point p(1, 1);
	display(p);	//p.display();
}

// ���: ����� �������� �ʴ� ��� �Լ��� ��쿡�� �ݵ�� const Ű���带 ������!
// -> ��� ��ü�� ��� �Լ��� ȣ���� �� �ֱ� ����