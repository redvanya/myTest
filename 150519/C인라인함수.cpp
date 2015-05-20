#include <iostream>
using namespace std;

#if 0
//int add(int a, int b) {
//	int result = a + b;
//	return result;	// mov eax, result
//					// ret
//}
//
//void main() {
//	int result;
//	add(1, 2);	// push 2 -> push 1 -> call add
//	__asm { mov result, eax }	// �Լ� ȣ�⿡ ���� ����� ũ��
//	cout << result << endl;
//}

// �ζ��� �Լ�: �Լ��� ȣ�� �ڵ尡 �Լ��� ���� �ڵ�� ġȯ�Ǵ� �Լ�
// �������� ��ȯ�ϴ� ���: cl.exe ���ϸ�.cpp /FAs
	   int		  add(int a, int b) { return a + b; }
inline int inline_add(int a, int b) { return a + b; }

void main() {
	int n = add(1, 1);
	int m = inline_add(1, 1);
}

/* cl.exe ���ϸ�.cpp /FAs /Ob1
; 7    : void main() {

push	ebp
mov	ebp, esp
sub	esp, 8

; 8    : 	int n = add(1, 1);

push	1
push	1
call	?add@@YAHHH@Z				; add
add	esp, 8
mov	DWORD PTR _n$[ebp], eax

; 9    : 	int m = inline_add(1, 1);

mov	eax, 1
add	eax, 1
mov	DWORD PTR _m$[ebp], eax

; 10   : }
*/

/* ����ȭ �ɼ� /Ob1 ������ ��
; 7    : void main() {

push	ebp
mov	ebp, esp
sub	esp, 8

; 8    : 	int n = add(1, 1);

push	1
push	1
call	?add@@YAHHH@Z				; add
add	esp, 8
mov	DWORD PTR _n$[ebp], eax

; 9    : 	int m = inline_add(1, 1);

push	1
push	1
call	?inline_add@@YAHHH@Z			; inline_add
add	esp, 8
mov	DWORD PTR _m$[ebp], eax

; 10   : }
*/

#endif

#if 0 // �����Ϸ��� �ζ��� ����� �����ϴ� ��� 1. �Լ� �����͸� ����ϴ� ���
int foo() { return 0; }
inline int goo() { return 0; }

void main() {
	int n = foo();	// call
	int m = goo();	// inline

	int(*fp)();
	int k;

	cin >> k;
	if (k == 0)	fp = foo;
	else goo;
	fp();	// call or inline? call! - �ζ����� ������Ÿ�ӿ� ��ȯ ������, ������� ���� ��Ÿ�� �� �� �� �ֱ� ������ ������ call�� �Ѵ�
}
#endif

#if 0	// �����Ϸ��� �ζ��� ����� �����ϴ� ��� 2. ���ȣ���� �ϴ� ���
// ����� ġȯ�� �Ŀ� �ڵ尡 �������� �ʱ� ������ �ڱ� �ڽ��� �θ� �� ����. ���� �ζ��� ��� ������.
inline int fact(int n) {	// �Լ� ������尡 ������ ũ�� ������ inline���� ����. but ������ call
	if (n <= 1)	return 1;
	return fact(n) * fact(n - 1);
}

void main() {
	int result = fact(5);
}
#endif

// �����Ϸ��� �ζ��� ����� �����ϴ� ��� 3. �Լ��� ���� �ڵ尡 �ſ� ū ���, �ζ��� ����� ����
