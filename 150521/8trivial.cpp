// trivial: �ڸ��ϴ� -> �ƹ� �ϵ� ���� �ʴ´�.
#include <iostream>
#include <cstdlib>
using namespace std;

#if 0
// trivial ������: �ڸ��� ������ -> �ƹ��� �ϵ� ���� �ʴ� ������
// 1. �θ� ���ų� �θ��� �����ڰ� �ڸ��ϰų�
// 2. ��ü�� ����� ���ų� ��ü�� ����� �����ڰ� �ڸ��ϰų�
// 3. �����Լ��� ���ų�
// 4. ����ڰ� ���� �����ڰ� ���ٸ�
// �����ڰ� �ڸ��ϴٶ�� �� �� �ִ� (�ƹ��ϵ� ���� �ʴ´�)
class Test {
public:
	/*virtual*/ void foo() {}	// virtual �߰��ϸ� ���α׷��� �״´�. ���� �ϴ� ���� �ִ�?

	// �⺻ ������
	Test() {}
};

int main() {
	Test* p = static_cast<Test*>(malloc(sizeof(Test)));
	p->foo();
}
#endif

#include <cstring>

// ��� Ÿ���� ���� �����ڴ� �ڸ����� �ʴ�
template<typename T> struct trait_trivial_copy { enum { value = false }; };
template<typename T> struct trait_trivial_ctor { enum { value = false }; };	// ������: ����ڰ� ���� �������� �� �ִ�
template<typename T> struct trait_trivial_dtor { enum { value = false }; };	// �Ҹ���

// �ٸ� �⺻ Ÿ���� �ڸ��ϴ�
#define BASIC_TYPE_TRAITS(T)	\
template<> struct trait_trivial_copy<T> { enum { value = true }; };	\
template<> struct trait_trivial_ctor<T> { enum { value = true }; };	\
template<> struct trait_trivial_dtor<T> { enum { value = true }; };

BASIC_TYPE_TRAITS(bool)
BASIC_TYPE_TRAITS(char)
BASIC_TYPE_TRAITS(short)
BASIC_TYPE_TRAITS(int)
BASIC_TYPE_TRAITS(long)
BASIC_TYPE_TRAITS(float)
BASIC_TYPE_TRAITS(double)

struct Point {
	int x, y;	// ��������ڰ� ���� ���縸 �����ϱ� �ڸ��ϴ�
};
BASIC_TYPE_TRAITS(Point)

// http://androidxref.com/5.1.0_r1/xref/frameworks/rs/cpp/util/TypeHelpers.h#151
template<typename T>
void copy_type(T* dst, T* src, size_t size) {
	if (trait_trivial_copy<T>::value == false) {	// ���� �����ڰ� �ڸ����� �����Ƿ� ���� �����ڸ� ����Ѵ�
		while (size--) {
			new(dst) T(*src);	// ���� ������ ����� ȣ�� (Placement New)
			++dst, ++src;
		}
	}
	else {	// ���� �����ڰ� �ڸ��ϴٸ� ���� �����ڸ� ȣ���� �ʿ䰡 �����Ƿ� �׳� �����Ѵ�
		memcpy(dst, src, sizeof(T)*size);
	}

}

//template<typename T>
//void copy_type(T* dst, T* src, size_t size) {
//	memcpy(dst, src, sizeof(T)*size);	// builtinŸ���� �ڸ������� ���������Ÿ���� �ڸ����� �ʴ� (�����Ҵ� ���� ��� double free�Ͼ)
//	// ��� ���ڷ� ���� T�� �ڸ����� �� ���� �� �� ������?
//}

int main() {
	char src[10] = "hello";
	char dst[10];
	//strcpy(dst, src);
	copy_type(dst, src, 10);
	cout << dst << endl;
	
}