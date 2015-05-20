// weak pointer �̾߱� : ���� ����� �������� �ʴ� ������
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
	//Node* node1 = new Node;	// �ڵ����� �Ҹ��ڰ� �Ҹ��� ���� ����Ʈ ������ ���
	//Node* node2 = new Node;

	shared_ptr<Node> node1(new Node);	// ������� 1
	shared_ptr<Node> node2(new Node);

	node1->next = node2;	// �Ҹ��ڰ� �ȺҸ�. �޸� ��������
	node2->next = node1;	// �ΰ��� ��ü�� ���� ����� 2 -> 1 : ��ȣ ������ ����
	// ���ο� ����ϴ� �����ʹ� weak pointer�� ���
	// strong pointer�� ��ȣ ������� �޸𸮰� ��ȯ���� �ʴ� ������ �߻� -> weak pointer ź��
	// Android������ ���� : SP(strong), WP(weak), UP(unique)
}
