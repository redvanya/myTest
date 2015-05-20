#include <iostream>
using namespace std;

// �Ϲ�ȭ ���α׷��� (generic programming)
#if 0
int main() {

	// �˻� ����
	// 1. ���� ��ġ, ����
	// 2. ���� ��ġ, �������� ���� ��ġ (PTE: post-the-end)
	char* s = "abcdefg";
	char* p = strchr(s, 'c');
	if (p == 0) {
		cout << "not found" << endl;
	} else {
		cout << "found" << endl;
	}
}
#endif

#if 0	//�˻� ������ �Ϲ�ȭ �մϴ�
char* xstrchr(char* first, char* last, char ch) {
	while (first != last && *first != ch)	// last�� �������� ���� ��ġ. ������� ���ٸ� ��ã�� ��
		++first;
	return first;	// ã�Ҵٸ� (*first == ch) �� ��ġ�� ��ȯ, ��ã���� ��� (first == last) �������� ���� ��ġ ��ȯ
}

// ������: �˻� �������� �Ϲ�ȭ �Ǿ����� Ÿ�Կ� ���ؼ��� �Ϲ�ȭ ���� ����
int main() {
	char* str = "abcdefg";
	char* p = xstrchr(str, str + 4, 'c');	// �κ� �˻� ��, ������ ��ġ�� �Ѱ��־��� ��� ã������ �ƴ��� �� �� ����
											// ������ ��ġ�� �˻� �����̰� null�� �ƴϱ� ����
											// �׷��� �������� ������ �ѱ����ν� �������� ������ ��� ��ã�� ������ ����
	if (p == str + 4)	cout << "not found" << endl;
	else cout << "found" << endl;
}
#endif

// ��� Ÿ�Կ� ���� ó���� �����ϵ��� �����ϱ�
// ������: ȣȯ�Ǵ� Ÿ�Կ� ���� �������� �ʴ´�
// -> ���ø��� ���ڸ� �ϳ� �� �߰��ϱ�
// ������: array�� �ǰ�, list�� ���� ���� ���� �ʴ´�. ++ ������ ���� �ʱ� ����
template <typename T1, typename T2>
T1* xfind(T1* first, T1* last, T2 ch) {
	while (first != last && *first != ch)
		++first;
	return first;
}

int main() {
		double arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };	// 5�� �˻�
		//double* ip = xfind(arr, arr + 5, 5);	// 5�� int���̶� type checking�� ���� ������ �߻�
												// �׷��� builtin Ÿ���� 5�� 5.0�� ����. �� ȣȯ��
		double* ip = xfind(arr, arr + 5, 5);	// �׷��� Ÿ���� �ΰ��� ����
		if (ip == arr + 5)	cout << "not found" << endl;
		else	cout << "found" << endl;
}

//int main() {
//	char* str = "abcdefg";
//	char* p = xfind(str, str + 4, 'c');
//	if (p == str + 4)	cout << "not found" << endl;
//	else cout << "found" << endl;
//
//	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };	// 5�� �˻�
//	int* ip = xfind(arr, arr + 5, 5);
//	if (ip == arr + 5)	cout << "not found" << endl;
//	else	cout << "found" << endl;
//}