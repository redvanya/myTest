// 함수 오버로딩 이야기: 같은 이름의 메소드를 중복 정의 할 수 있다.
// 1. parameter개수 or 타입이 다르다
// 2. 리턴타입은 포함되지 않는다

// 함수 오버로딩의 원리: C++ 컴파일러가 함수의 이름을 변경(name mangling/decoration)하기 때문
// 이름 변경 방법: 함수의 이름과 파라미터를 조합

// 어셈블리어 코드 생성 방법
// windows: cl.exe 파일명.cpp /FAs		-> 파일명.asm
//   linux: g++ -S 파일명.cpp			-> 파일명.s

   int square(int x)    { return x*x; }
double square(double x) { return x*x; }
void main(){
	int a = square(3);
	double b = square(3.3);
}