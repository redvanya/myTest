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
	Point* p = static_cast<Point*>(operator new(sizeof(Point)));	// �����ڰ� ȣ����� �ʴ´� -> operator new()�� �Լ�?!
	cout << p << endl;
}

// new �����ڰ� �ϴ���
// 1. �޸� ���� �Ҵ�. �����Ѵٸ� null ����
// 2. ���� �Ҵ翡 �����ϰ� �ǿ����ڰ� ����� ���� Ÿ���̶�� ������ ȣ��
// 3. lvalue Ÿ������ �� ��ȯ

//void main() {
//	Point* p1 = static_cast<Point*>(malloc(sizeof(Point)));	// �����ڰ� ȣ����� �ʴ´�
//	Point* p2 = new Point;	// �����ڰ� ȣ��ȴ�
//}
#endif

#if 0
// new �������� ���� ���
// new �������� ù ��° ���ڴ� ������ size
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
	// ������� �������� �ʴ´ٸ� �����ε� �ؼ� �� �� �ִ�
	int* p1 = new int;	// �ǿ������� ũ�⸦ ��� ���ñ�? (������ sizeof�� ����) -> ���⼭ new �����ڿ��� �ǿ������� ũ�⸦ ��Ÿ���� ���ڰ� �ϳ� �ִٰ� �߷� ����
	int* p2 = new("�̷���") int;	// ù ��° ���ڴ� �����ʿ� ������ ������ �����ε��� �Լ��� �ι�° ���ڸ� ���� ���ؼ��� �̷� ������ ��� ��.
	int* p3 = new(__FILE__, __LINE__) int;
}
#endif

#if 0
class Point {
public:
	Point() { cout << "Point()" << endl; }
	~Point() { cout << "~Point()" << endl; }
};

// �̹� ǥ�ؿ��� void* operator new(size_t, void*)�� �����ϰ� �ִ� -> ����� ������ ȣ���� �ʿ��ϴϱ�
//void* operator new(size_t size, void* p){
//	return p;
//}

void main() {
	Point* p = static_cast<Point*>(malloc(sizeof(Point)));
	new(p) Point;	// new���� �����ڸ� ȣ�����ִϱ� new�� �����ε��� �Լ��� ��������� ������ ȣ�� ����
}

//void main() {
//	Point p;
//	p.~Point();	// �Ҹ��ڴ� ��������� ȣ�� ���� - main�� ������ �ʾ� ���� ������ü�� �������� �ʾ����� �Ҹ��� ȣ�� ����
//	p.Point();	// �����ڴ� �ȵȴ� -> �޸𸮸� �Ҵ� �� ��������� �θ� �� �ִ�?
//}
#endif

// �������� ����� ȣ���� �ʿ��� ��� : Placement New
class Point {
public:
	Point(int a, int b) { cout << "Point(" << a << " ," << b << ")" << endl; }
};

void main() {
	//Point* p1 = new Point(0, 0);	// ���������� ��ü �Ҵ�
	//Point* p2 = new Point[10];	// Point�� �⺻�����ڰ� ���� ���¿��� �迭�� ����� ������?
	Point* p2 = static_cast<Point*>(malloc(10 * sizeof(Point)));	// 1. ���� ������ ���� �޸� �Ҵ�
	for (int i = 0; i < 10; i++)	// 2. 10���� ��ü�� ���� ������ ȣ��
		new(p2 + i) Point(0, 0);	//new(&p2[i]) Point(0, 0);
}
