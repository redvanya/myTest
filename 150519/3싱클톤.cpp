// 싱글톤 정책을 자동화해 봅시다 (복사 2.cpp)

#include <iostream>
using namespace std;

// 복사와 대입을 금지하는 매크로
#define MAKE_NO_COPY(CLASSNAME)				\
	private:								\
		CLASSNAME(const CLASSNAME&);		\
		void operator=(const CLASSNAME&);

// 싱글톤 정책을 자동화하기 위한 매크로
# define DECLARE_SINGLETON(CLASSNAME)	\
		MAKE_NO_COPY(CLASSNAME)			\
	private: CLASSNAME() {}				\
		static CLASSNAME* pInstance;	\
	public:	static CLASSNAME& getInstance();

#define IMPLEMENT_SINGLETON(CLASSNAME)				\
	CLASSNAME* CLASSNAME::pInstance = 0;			\
	CLASSNAME& CLASSNAME::getInstance() {			\
		if (pInstance == 0)							\
			pInstance = new CLASSNAME;				\
		return *pInstance;							\
	}
// 위의 코드는 라이브러리 또는 프레임 워크에서 제공하는 코드입니다.
// ---------------------------------------------------
// 아래는 사용자 구현 코드

class Cursor {
	DECLARE_SINGLETON(Cursor)
};
IMPLEMENT_SINGLETON(Cursor)

int main() {
	Cursor& c1 = Cursor::getInstance();
	Cursor& c2 = Cursor::getInstance();

	cout << "&c1 = " << &c1 << endl;
	cout << "&c2 = " << &c2 << endl;
}