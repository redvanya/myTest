#include <iostream>
using namespace std;

#if 0
void init_int(int a)	{ a = 0; }
void init_arr(int a[])	{ a[0] = 0; }

void main() {
	int i = 10;
	int a[10] = { 20 };

	init_int(i);	// init_int(10); -> �Ⱥ���. call by value
	cout << i << endl;

	// ������ ������ ���� : ���ü�� Ÿ�� * ������;
	int* pInt = &i;

	getchar();

	init_arr(a);	// init_ar(0x12FF60); -> 0���� �ʱ�ȭ��. array�� pointer�� ����Ǿ� �Ѿ.
	cout << a[0] << endl;

	//int(* pArr)[1] = a;	// ���� a�� int[1] Ÿ�������� �Ʒ�ó�� int�� ������Ÿ��, �� ù��° (a[0])�� ������ Ÿ������ ��ҵȴ�.
	int* pArr = a;	// decay: �迭�� Ÿ���� �迭 ��ü���� ù ��° ������ Ÿ������ ��� �Ǵ� ��ȭ
	cout << sizeof a << endl;	// �迭���� �����ϰ� decay�� �߻����� �ʴ� ���� sizeof ������
}
#endif

#if 0
// Argument Decay: ���ø����� �����̹߻�

// (T)�� ���ڷ� ���� ���: �迭�� �Լ��� decay�� �߻��Ѵ�
template<typename T> void type_check_val(T t) {
	cout << typeid(t).name() << endl;
}

// ����(&T)�� ���ڷ� ���� ���: ��Ȯ�� �迭�� Ÿ������ ���޵�
template<typename T> void type_check_ref(T& t) {
	cout << typeid(t).name() << endl;
}

void main() {
	int i = 0;
	type_check_val(i);	// int�� ���´�
	type_check_ref(i);	// int�� ���´�

	int arr[3];
	type_check_val(arr);	// int * �� ���´� - �������� C�� ������ ���� ��ü �迭�� ù��° ������ ������ Ÿ������ ���޵Ǵ� decay�� �߻��Ѵ�.
	type_check_ref(arr);	// int [3] �� ���´� - ��Ȯ�� �迭�� Ÿ��

	type_check_val("hello");	// char const *
	type_check_ref("hello");	// char const [6]

	type_check_val(main);	// �Լ� ������: int (__cdecl*)(void)
	type_check_ref(main);	// �Ϲ� �Լ� �״�� ����: int __cdecl(void)
}
#endif

// ��������
template<typename T> void foo(T a, T b) {
	cout << "called foo(T)" << endl;
}

template<typename T> void goo(T& a, T& b) {
	cout << "called goo(T&)" << endl;
}

void goo(const char* a, const char* b) {
	cout << "called goo(char*)" << endl;
}

// �����Ϸ��� �Ϲ� �Լ��� �Լ� ���ø��� �����ε� �� ���, ã�� ����
// �Ϲ� �Լ� -> �Լ� ���ø�

void main() {
	foo("kk", "hhhh");	// void foo(const char*, const char*);


	goo("kkk", "hhh");	// void goo(const char[3], const char[3]) -> �� �迭�� ���̰� ���Ƽ� T&�� ���� �� �ִ�
	goo("kkkasdfasdf", "hhhhasdfasfd");	// �� �Ķ������ ���̰� �޶� �ٸ� Ÿ������ �ν�. ���ø� �� �� ���� -> �Ϲ� �Լ� �����ε�
}