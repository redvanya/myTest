// �����Ϸ��� �����ε��� �Լ��� ã�� ���
#include <iostream>
using namespace std;

class Float {
public:
	float val;
	/*explicit*/ Float(float f) : val(f) {}
};
//void foo(float f)	 { cout << "foo(float)" << endl; }		// 1. ���� ��ġ: Ÿ���� �Ϻ��ϰ� ��ġ�� �Լ��� ã��
//void foo(double f) { cout << "foo(double)" << endl; }		// 2. �°�: �������� �ս��� ���� Ÿ������ ��ȯ. floatŸ���� �Լ��� ���� ��, ������ ����� �� �ְ� ���
//void foo(int f)    { cout << "foo(int)" << endl; }		// 3. �⺻ Ÿ���� ���, ������ �ս��� �߻��ϴ��� ��ȯ �� ���� (�Ͻ��� ��ȯ ��� - C���� ����ȣȯ���� ����)
void foo(Float f)  { cout << "foo(Float)" << endl; }		// 4. ����� ���� ��ȯ ��, ȣ��
void foo(...)		 { cout << "foo(...)" << endl; }		// 5. ��������

int main(){
	foo(3.14f); // ã�� ����: 1->2->3->4->5
}