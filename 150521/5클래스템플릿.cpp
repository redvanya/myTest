#include <iostream>

#if 0
template<typename T> class Stack {
public:
	// ������
	// Stack<T> {}	// 1. ��ǥ��
	//Stack() {}	// 2. ǥ��

	// ���� ������
	// Stack(const Stack& s) {}	// 1. Ŭ���� ���ο����� ���
	// Stack(const Stack<T>& s) {}	// 2. ��Ȯ�� ����

	// ��� �Լ�
	void push(const T& data);

	// �ٸ� Ÿ���� ���ڷ� �ϴ� �Լ��� ��� �Լ� ���ø����� �����ؾ� �Ѵ�
	template<typename U> void foo(const U& u); // {}
};

// ��� �Լ��� �ܺ� ����
template<typename T>
void Stack<T>::push(const T& data) {}

template<typename T> template <typename U>
void Stack<T>::foo(const U& u) {}

void main() {
	Stack<int> s;
}
#endif

// ��� �Լ� ���ø��� �ʿ��� ���
template<typename T> class Complex {
	T real, image;	// 1 + 1i
	/*template<typename U>*/ friend class Complex;
public:
	Complex(T r, T i) : real(r), image(i) {}
	template <typename U>
	Complex(const Complex<U>& o) : real(o.real), image(o.image) {}
	
};

void main() {
	Complex<int> c1(1, 1);
	Complex<double> c2 = c1;
}