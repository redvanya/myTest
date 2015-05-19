#include <iostream>
using namespace std;

class Cursor {
	// 1. 사용자로부터 객체의 임의 생성을 막기 위해여 생성자를 private 영역에 정의
	Cursor() {}
	static Cursor* pInstance;
	
	// 3. 복사와 대입을 금지하기 위해 복사 생성자와 대입 연산자 함수를 private 영역에 정의해야 함ㅣ
	Cursor(const Cursor&);					// = delete;
	void operator=(const Cursor& c);		// = delete;
public:
	void foo() {
		// 외부에서는 객체 생성을 막을 수 있지만, 내부 생성은 막을 수 없다 (컴파일러는 막을 수 없지만, 링커에서는 할 수 있다)
		Cursor c;
		Cursor c2 = c;
		Cursor c3;
		c3 = c;
	}

	// 2. 유일한 객체를 반환하기 위한 정적 인터페이스 제공
	static Cursor& getInstance() {
		//static Cursor cursor;
		//return cursor;

		// 객체를 리턴할 때는 참조로 리턴하는 것이 안전
		// 포인터로 리턴하면 포인터를 이용해서 삭제가 가능해짐. 리스크 생김
		if (pInstance == 0)
			pInstance = new Cursor;
		return *pInstance;
	}
};
Cursor* Cursor::pInstance = 0;

int main() {
	Cursor& c1 = Cursor::getInstance();	// Cursor.getInstance();
	Cursor& c2 = Cursor::getInstance();
	
	cout << "&c1 = " << &c1 << endl;
	cout << "&c2 = " << &c2 << endl;

	//Cursor c3 = c1;		// 객체의 복사로 인한 새로운 객체 생성. 싱글톤이 아니다.
	//cout << "&c3 = " << &c3 << endl;
}