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
//	__asm { mov result, eax }	// 함수 호출에 대한 비용이 크다
//	cout << result << endl;
//}

// 인라인 함수: 함수의 호출 코드가 함수으 기계어 코드로 치환되는 함수
// 어셈블리어로 변환하는 방법: cl.exe 파일명.cpp /FAs
	   int		  add(int a, int b) { return a + b; }
inline int inline_add(int a, int b) { return a + b; }

void main() {
	int n = add(1, 1);
	int m = inline_add(1, 1);
}

/* cl.exe 파일명.cpp /FAs /Ob1
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

/* 최적화 옵션 /Ob1 안줬을 때
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

#if 0 // 컴파일러가 인라인 명령을 무시하는 경우 1. 함수 포인터를 사용하는 경우
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
	fp();	// call or inline? call! - 인라인은 컴파일타임에 변환 되지만, 사용자의 값은 런타임 시 알 수 있기 때문에 무조건 call을 한다
}
#endif

#if 0	// 컴파일러가 인라인 명령을 무시하는 경우 2. 재귀호출을 하는 경우
// 기계어로 치환된 후엔 코드가 남아있지 않기 때문에 자기 자신을 부를 수 없다. 따라서 인라인 명령 무시함.
inline int fact(int n) {	// 함수 오버헤드가 굉장히 크기 때문에 inline으로 변경. but 여전히 call
	if (n <= 1)	return 1;
	return fact(n) * fact(n - 1);
}

void main() {
	int result = fact(5);
}
#endif

// 컴파일러가 인라인 명령을 무시하는 경우 3. 함수의 기계어 코드가 매우 큰 경우, 인라인 명령을 무시
