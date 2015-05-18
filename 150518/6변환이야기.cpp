// ��ȯ�� ���輺
#include <iostream>
using namespace std;

#if 1
class Complex {
public:
	int r, i;

	Complex(int a = 0, int b = 0) : r(a), i(b) {}

	// ������ �����ε�
	// � Ŭ������ ��ȯ �����ڸ� ����� ���̶�� ������ ��ȯ ������ ���ٴ�
	// ��ȯ �������̽��� �����ϴ� ���� �� ���� �� �ִ�.
	explicit operator int() { return r; }	// return Ÿ���� �ִ��� ������. �� ��� �������� �������
	int asReal() { return r; }
};

void foo(int i) {
	cout << "called foo(" << i << ")" << endl;
}

int main() {
	double d = 3.14;
	int i = d;	// �⺻ �����Ϳ� ���ؼ� ������ �ս��� �ִ��� �Ͻ��� ��ȯ�� �Ͼ��. standard conversion(�⺻��ȯ)
	foo(i);		// cout << i << endl;

	Complex c(1, 1);	// 1 + 1i
	int real = c;		// �̼�������, ����� ������ �ȵǾ �Ǽ��� ����Ǿ�� ���� �ʳ�? ����� ���� Ÿ�Ե� �⺻Ÿ�԰� ���� �����ϵ��� ���������� ����
						// int(c) -> c.operator int();
						// ��ȯ ������ ���� ���� ? ���װ� �ִ�
	// cout << real << endl;
	foo(c);		// �Ǹ� �ȵǴµ� �ȴ�! ���� - �츮�� �ǵ����� ���� �ڵ�. explicit ���� ������ �� ����
}
#endif

#if 0
class Int32 {
public:
	int val;
	// ��ȯ �����ڴ� ���ڰ� �ϳ��� �����ڴ� ��� ��ȯ �����ڰ� �� �� �ִ�
	// ��ȯ �����ڴ� �����Ϸ��� ���� ȣ��� �� �ִ� (�Ͻ��� ��ȯ)
	// ���ڰ� �ϳ��� �������� ��ȯ �����ڷν� ����� �����Ϸ��� explicit
	explicit Int32(int i = 0): val(i) {}
	
};

void foo(Int32 i){
	cout << "called foo(" << i.val << ")" << endl;

}

void main() {
	Int32 i(20);
	// coutn << i.val << endl;
	foo(i);	// OK

	int n = 30;
	foo(n); // foo(Int32(n)); -> �Ǵµ� �Ǹ� �ȵ�! ������ ���� ����
}
#endif