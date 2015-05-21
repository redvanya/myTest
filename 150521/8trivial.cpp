// trivial: 자명하다 -> 아무 일도 하지 않는다.
#include <iostream>
#include <cstdlib>
using namespace std;

#if 0
// trivial 생성자: 자명한 생성자 -> 아무런 일도 하지 않는 생성자
// 1. 부모가 없거나 부모의 생성자가 자명하거나
// 2. 객체형 멤버가 없거나 객체형 멤버의 생성자가 자명하거나
// 3. 가상함수가 없거나
// 4. 사용자가 만든 생성자가 없다면
// 생성자가 자명하다라고 할 수 있다 (아무일도 하지 않는다)
class Test {
public:
	/*virtual*/ void foo() {}	// virtual 추가하면 프로그램이 죽는다. 뭔가 하는 일이 있다?

	// 기본 생성자
	Test() {}
};

int main() {
	Test* p = static_cast<Test*>(malloc(sizeof(Test)));
	p->foo();
}
#endif

#include <cstring>

// 모든 타입의 복사 생성자는 자명하지 않다
template<typename T> struct trait_trivial_copy { enum { value = false }; };
template<typename T> struct trait_trivial_ctor { enum { value = false }; };	// 생성자: 사용자가 새로 정의했을 수 있다
template<typename T> struct trait_trivial_dtor { enum { value = false }; };	// 소멸자

// 다만 기본 타입은 자명하다
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
	int x, y;	// 복사생성자가 얕은 복사만 있으니까 자명하다
};
BASIC_TYPE_TRAITS(Point)

// http://androidxref.com/5.1.0_r1/xref/frameworks/rs/cpp/util/TypeHelpers.h#151
template<typename T>
void copy_type(T* dst, T* src, size_t size) {
	if (trait_trivial_copy<T>::value == false) {	// 복사 생성자가 자명하지 않으므로 복사 생성자를 사용한다
		while (size--) {
			new(dst) T(*src);	// 복사 생성자 명시적 호출 (Placement New)
			++dst, ++src;
		}
	}
	else {	// 복사 생성자가 자명하다면 복사 생성자를 호출할 필요가 없으므로 그냥 복사한다
		memcpy(dst, src, sizeof(T)*size);
	}

}

//template<typename T>
//void copy_type(T* dst, T* src, size_t size) {
//	memcpy(dst, src, sizeof(T)*size);	// builtin타입은 자명하지만 사용자정의타입은 자명하지 않다 (동적할당 했을 경우 double free일어남)
//	// 어떻게 인자로 들어온 T가 자명한지 안 한지 알 수 있을까?
//}

int main() {
	char src[10] = "hello";
	char dst[10];
	//strcpy(dst, src);
	copy_type(dst, src, 10);
	cout << dst << endl;
	
}