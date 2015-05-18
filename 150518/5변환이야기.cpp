#include <stdlib.h>

#if 0
void main() {
	
	//char* p = malloc(sizeof(char)); //ERROR void pointer는 *,+,- 안됨. 따라서 구체적인 타입으로 캐스팅해서 써야 한다 (논리적으로 합당)
	//char* p = (char*)malloc(sizeof(char)); //이렇게 하면 되긴 하지만, C와의 하위호환성을 위해 되는 것으로, C++에서는 논리적으로 안됨.
	
	// 1. static_cast: 이상적인 형 변환을 할 때 사용
	char* p = static_cast<char*>(malloc(sizeof(char)));

	int n = 1;
	//char* p = (char*)&n;	// 컴파일러의 타입 체크 기능을 끄게 됨
	//char* p = static_cast<char*>(&n);	// 컴파일러 입장에서 이건 말도 안되는 코드. 하지만 테크닉적으로 쓰고 싶다
	
	// 2. reinterpret_cast: 비 이성적인 형 변환을 할 때 사용
	// C 언어와 같이 대부분의 형 변환을 지원함
	char* p = reinterpret_cast<char*>(&n);	// 재해석
}
#endif

#include <iostream>
using namespace std;

void main() {
	const int n = 20;

	// 직접 참조로는 바꿀 수 없지만, 포인터를 이용한 간접 참조로 변경 가능
	// C에서는 100% 사용자의 코드를 신뢰하기 때문에 되는 코드
	// C++에서는 안됨.
	//int* p = &n;
	//*p = 0;			

	//int* p = reinterpret_cast<int*>(&n);

	// 3. const_cast: 객체의 논리적 상수성을 비상수 객체로 캐스팅
	// 가급적 사용을 자제하는 것이 좋음
	int* p = const_cast<int*>(&n);	// 반드시 수행을 해야만 한다면 이 cast를 사용. const_cast를 써야 한다면 설계가 잘못되었다는 가능성이 큼. 가급적 쓰지마라
	*p = 0;
}

// 4. dynamic_cast: android RTTI를 만들 때 같이 함