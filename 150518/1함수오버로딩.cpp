// �Լ� �����ε� �̾߱�: ���� �̸��� �޼ҵ带 �ߺ� ���� �� �� �ִ�.
// 1. parameter���� or Ÿ���� �ٸ���
// 2. ����Ÿ���� ���Ե��� �ʴ´�

// �Լ� �����ε��� ����: C++ �����Ϸ��� �Լ��� �̸��� ����(name mangling/decoration)�ϱ� ����
// �̸� ���� ���: �Լ��� �̸��� �Ķ���͸� ����

// ������� �ڵ� ���� ���
// windows: cl.exe ���ϸ�.cpp /FAs		-> ���ϸ�.asm
//   linux: g++ -S ���ϸ�.cpp			-> ���ϸ�.s

   int square(int x)    { return x*x; }
double square(double x) { return x*x; }
void main(){
	int a = square(3);
	double b = square(3.3);
}