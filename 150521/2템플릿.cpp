// template
// C++ �̶�	1. ���������� : C�� subset���� ������ �ֱ� ����
//			2. ��ü������ : +a�� ��ü ���� ������ �����Ѵ�
//			3. �Ϲ�ȭ ���α׷��� : ���ø�
//			4. ��Ÿ ���α׷��� : ���ø� ���� - factorial���� ��������� ���ϴ� ���� ������ Ÿ�ӿ� ���� �� �ִ�. ���ɻ��� ������尡 ����
//							   �ڹٿ����� ����ϰ� generic�� �����ߴ�

#include <iostream>
using namespace std;

#if 0
// 1. �Լ� ���ø�
template<typename T> T Max(T a, T b) { return a > b ? a : b; }

// 2. Ŭ���� ���ø�
template<typename T> class Stack {
	T* arr;
public:
	void push_front(T data) {}
};

void main() {
	cout << Max<int>(1, 2) << endl;	// ���� �� Ÿ���� �Ѱ���� �Ѵ� - ����� Ÿ�� ����
	cout << Max(1, 2) << endl;		// Ÿ���� �����ص� �����Ϸ��� ���� ������ Ÿ���� Ȯ���ؼ� ���ø��� ����� - �Ͻ��� �߷� ����

	//Stack s;		// ERROR, Ŭ���� ���ø��� �Ͻ��� �߷� �Ұ���
	Stack<int> s;	// OK, Ŭ���� ���ø��� Ÿ���� ��������� ����ؾ� �Ѵ�. Stack�� ���ø��̰� Stack<int>�� ������ Ÿ��
	s.push_front(20);
}
#endif

#if 0
// ���ø� ����
// �����ø�/�⺻ ���ø� (primary template) : ��� Ÿ���� �� �ȴ�.
template<typename T> class Stack {
public:
	void push() { cout << "T" << endl; }
};

// �κ� ����ȭ ���ø� (partial specializer) : �ϳ��� Ÿ������ �����ε� ����
// Ư�� Ÿ�Կ� ���ؼ��� �ٸ��� �����ϵ��� �ϰ� �ʹ�
template<typename T> class Stack<T*> {
public:
	void push() { cout << "T*" << endl; }
};

// ����ȭ ���ø� (specializer)
template<> class Stack<char*> {
public:
	void push() { cout << "char*" << endl; }
};

int main() {
	Stack<int> s1;	s1.push();
	Stack<int*> s2;	s2.push();
	Stack<char*> s3;	s3.push();
}
#endif

// ���ø� ��Ÿ ���α׷��� : ������ ������ ���� ������ ���������� �й������θ� ����.

// ��Ÿ�ӿ� �����ϴ� �Լ�
int fact(int n) {
	if (n <= 1)	return 1;
	return n * fact(n - 1);
}

// ��� ���� N�� ���ؼ� ó���ϴ� Ŭ���� ����
template<int N> struct Fact {
	enum { num = N * Fact<N - 1>::num };
};

// N�� 1�� ��쿡 ���� ó���� ����ȭ ���
template<> struct Fact < 1 > {
	enum { num = 1 };
};

void main() {
	//cout << fact(5) << endl;	// ��Ÿ�� ����
	cout << Fact<5>::num << endl;	// ������ Ÿ�ӿ� ��� �Ϸ�
	
}