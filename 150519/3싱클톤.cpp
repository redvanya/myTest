// �̱��� ��å�� �ڵ�ȭ�� ���ô� (���� 2.cpp)

#include <iostream>
using namespace std;

// ����� ������ �����ϴ� ��ũ��
#define MAKE_NO_COPY(CLASSNAME)				\
	private:								\
		CLASSNAME(const CLASSNAME&);		\
		void operator=(const CLASSNAME&);

// �̱��� ��å�� �ڵ�ȭ�ϱ� ���� ��ũ��
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
// ���� �ڵ�� ���̺귯�� �Ǵ� ������ ��ũ���� �����ϴ� �ڵ��Դϴ�.
// ---------------------------------------------------
// �Ʒ��� ����� ���� �ڵ�

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