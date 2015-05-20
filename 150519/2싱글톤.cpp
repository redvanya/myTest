#include <iostream>
using namespace std;

class Cursor {
	// 1. ����ڷκ��� ��ü�� ���� ������ ���� ���ؿ� �����ڸ� private ������ ����
	Cursor() {}
	static Cursor* pInstance;
	
	// 3. ����� ������ �����ϱ� ���� ���� �����ڿ� ���� ������ �Լ��� private ������ �����ؾ� �Ԥ�
	Cursor(const Cursor&);					// = delete;
	void operator=(const Cursor& c);		// = delete;
public:
	void foo() {
		// �ܺο����� ��ü ������ ���� �� ������, ���� ������ ���� �� ���� (�����Ϸ��� ���� �� ������, ��Ŀ������ �� �� �ִ�)
		Cursor c;
		Cursor c2 = c;
		Cursor c3;
		c3 = c;
	}

	// 2. ������ ��ü�� ��ȯ�ϱ� ���� ���� �������̽� ����
	static Cursor& getInstance() {
		//static Cursor cursor;
		//return cursor;

		// ��ü�� ������ ���� ������ �����ϴ� ���� ����
		// �����ͷ� �����ϸ� �����͸� �̿��ؼ� ������ ��������. ����ũ ����
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

	//Cursor c3 = c1;		// ��ü�� ����� ���� ���ο� ��ü ����. �̱����� �ƴϴ�.
	//cout << "&c3 = " << &c3 << endl;
}