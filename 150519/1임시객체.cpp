#include <iostream>
using namespace std;

#if 0
class Int32 {
public:
	int val;

	Int32(int v = 0) : val(v) { 
		printf("Int32(%d): %p\n", v, this);
		//cout << "Int32() : " << val << endl; 
	}
	~Int32() {
		printf("~Int32(%d): %p\n", val, this);
		//cout << "~Int32() : " << val << endl; 
	}

	Int32(const Int32& o): val(o.val) {
		printf("복사생성자 Int32(%d): %p\n", val, this);
	}

	Int32 operator+(const Int32& o) {
		//Int32 temp(val + o.val);
		//return temp;

		return Int32(val + o.val);	// RVO (Return Value Optimization)
	}

	
};

void main() {
	int32 a = 10;
	int32 b = 20;
	int32 c;

	getchar();
	c = a + b;	// c = a.operator+(b)
	getchar();

	cout << c.val << endl;
}

/*
void main() {
//Int32();
//getchar();

// builtin type에서는 임시객체가 고려대상이 아님.
// 하지만 객체에 대해서는 임시 객체의 크기가 크기때문에 고려해줘야 함.
int a = 10;
int b = 20;
int c;

c = a + b;
cout << c << endl;
}
*/
#endif

struct Int32 {
	int val;
};
Int32 i = { 10 };
Int32 getInt32A() { return i; }
Int32& getInt32B() { return i; }

int main() {
	getInt32A().val = 0;
	cout << i.val << endl;

	getchar();

	// 지역 객체가 아닌 참조객체로 리턴해야 임시 객체를 막을 수 있다
	getInt32B().val = 0;
	cout << i.val << endl;

}