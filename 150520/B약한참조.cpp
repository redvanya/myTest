// weak pointer 이야기 : 참조 계수를 관리하지 않는 포인터
#include <iostream>
#include <memory>
using namespace std;

struct Node {
	int data;
	//Node* next;
	weak_ptr<Node> next;
	~Node() { cout << "~Node()" << endl; }
};

void main() {
	//Node* node1 = new Node;	// 자동으로 소멸자가 불리기 위해 스마트 포인터 사용
	//Node* node2 = new Node;

	shared_ptr<Node> node1(new Node);	// 참조계수 1
	shared_ptr<Node> node2(new Node);

	node1->next = node2;	// 소멸자가 안불림. 메모리 누수현상
	node2->next = node1;	// 두개의 객체의 참조 계수가 2 -> 1 : 상호 참조의 문제
	// 내부에 사용하는 포인터는 weak pointer를 사용
	// strong pointer는 상호 참조라는 메모리가 반환되지 않는 문제가 발생 -> weak pointer 탄생
	// Android에서도 제공 : SP(strong), WP(weak), UP(unique)
}
