#include <stdlib.h>

#if 0
void main() {
	
	//char* p = malloc(sizeof(char)); //ERROR void pointer�� *,+,- �ȵ�. ���� ��ü���� Ÿ������ ĳ�����ؼ� ��� �Ѵ� (�������� �մ�)
	//char* p = (char*)malloc(sizeof(char)); //�̷��� �ϸ� �Ǳ� ������, C���� ����ȣȯ���� ���� �Ǵ� ������, C++������ �������� �ȵ�.
	
	// 1. static_cast: �̻����� �� ��ȯ�� �� �� ���
	char* p = static_cast<char*>(malloc(sizeof(char)));

	int n = 1;
	//char* p = (char*)&n;	// �����Ϸ��� Ÿ�� üũ ����� ���� ��
	//char* p = static_cast<char*>(&n);	// �����Ϸ� ���忡�� �̰� ���� �ȵǴ� �ڵ�. ������ ��ũ�������� ���� �ʹ�
	
	// 2. reinterpret_cast: �� �̼����� �� ��ȯ�� �� �� ���
	// C ���� ���� ��κ��� �� ��ȯ�� ������
	char* p = reinterpret_cast<char*>(&n);	// ���ؼ�
}
#endif

#include <iostream>
using namespace std;

void main() {
	const int n = 20;

	// ���� �����δ� �ٲ� �� ������, �����͸� �̿��� ���� ������ ���� ����
	// C������ 100% ������� �ڵ带 �ŷ��ϱ� ������ �Ǵ� �ڵ�
	// C++������ �ȵ�.
	//int* p = &n;
	//*p = 0;			

	//int* p = reinterpret_cast<int*>(&n);

	// 3. const_cast: ��ü�� ���� ������� ���� ��ü�� ĳ����
	// ������ ����� �����ϴ� ���� ����
	int* p = const_cast<int*>(&n);	// �ݵ�� ������ �ؾ߸� �Ѵٸ� �� cast�� ���. const_cast�� ��� �Ѵٸ� ���谡 �߸��Ǿ��ٴ� ���ɼ��� ŭ. ������ ��������
	*p = 0;
}

// 4. dynamic_cast: android RTTI�� ���� �� ���� ��