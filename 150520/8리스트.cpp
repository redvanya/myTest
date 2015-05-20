// ����Ʈ �����̳�
#include <iostream>
using namespace std;

#if 0
struct Node {
	int data;
	Node* next;
};

Node* head;

void insert_node(int data) {
	Node* temp = new Node;
	temp->data = data;
	temp->next = head;
	head = temp;
}

void display() {
	Node* node;
	system("cls");
	printf("[head] ");
	for (node = head; node != 0; node = node->next){
		printf("-> [%d] ", node->data);
	}
	getchar();
}

void main() {
	for (int i = 0; i < 5; i++) {
		insert_node(i + 1);
		display();
	}
}
#endif

#if 0	// class�� �����ϱ�
template<typename T> struct Node {
	T data;
	Node* next;
	Node(T d, Node* n) : data(d), next(n) {}
};

template<typename T> class slist {
	Node<T>* head;
public:
	slist() : head(0) {}
	void insert_node(T data) {
		head = new Node<T>(data, head);
	}
};

void main() {
	slist<int> s;
	for (int i = 0; i < 5; i++) {
		s.insert_node(i + 1);
	}
}

#endif

#include <vector>

// �����̳� ��Ҹ� ����Ű�� ����Ʈ ������ �����ϱ�
template<typename T> struct Node {
	T data;
	Node* next;
	Node(T d, Node* n) : data(d), next(n) {}
};

template<typename T> class slist_iterator {
	Node<T>* cur;
public:
	slist_iterator(Node<T>* p = 0) : cur(p) {}

	// ++obj; -> obj.operator++();
	inline slist_iterator operator++() {
		cur = cur->next;
		return *this;
	}
	inline T& operator*() { return cur->data; }

	// o1 != o2; -> o1.operator!=(o2);
	inline bool operator!=(const slist_iterator& o) { return cur != o.cur; }
	inline bool operator==(const slist_iterator& o) { return cur == o.cur; }
};

template<typename T> class slist {
	Node<T>* head;
public:
	slist() : head(0) {}
	void insert_node(T data) { head = new Node<T>(data, head); }

	typedef slist_iterator<T> iterator;	// ����ڰ� �̾ƾ� �� �ֵ���, ������ ���� ����� ���� ���� �ڵ嵵 ������ ����
	// ��� �����̳� �����ڴ� �����̳� ������ �ڷᱸ���� ���۰� ������ ���� ��ġ�� ��ȯ�ϴ� �Լ��� �����ϱ�� ����Ѵ�.
	iterator begin() { return iterator(head); }
	iterator end()   { return iterator(0); }
};

template <typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 ch) {
	while (first != last && *first != ch)	// ���⼭ T1�� ��ü�̱� ������ !=, *, ++ ���� �����ڰ� �ƴ�, �Լ���. �Լ��� ȣ���� ������尡 ũ��
		++first;							// -> �� ������ �����ε� �Լ��� �ζ������� �ٲٱ�
	return first;
}

void main() {
	slist<int> s;
	for (int i = 0; i < 10; i++) {
		s.insert_node(i * 10);
	}

	//slist_iterator<int> p1 = xfind(s.begin(), s.end(), 90);	// ����ڰ� ���ͷ������� �ɺ���(slist_iterator)�� �˾ƾ� �Ѵ�. -> .h�� ���� Ȯ���ؾ� ��
	slist<int>::iterator p1 = xfind(s.begin(), s.end(), 90);
	if (p1 == s.end())	cout << "not found" << endl;
	else	cout << "found" << endl;

	slist<int>::iterator p2;
	for (p2 = s.begin(); p2 != s.end(); p2++){
		cout << *p2 << endl;
	}

	// �Ʒ� vector�� ���� ���Ƶ�, �����̳ʴ� �⺻������ begin, end, iterator ����
	//vector<int> v;
	//v.begin();
	//v.end();
	//vector<int>::iterator;	
}

// find, sort, ... �� �� �����̳� ���� ����� x Ÿ�Ա��� �ϸ� ���Ѵ�
// �׷��� find, sort, ...�� �и��ϱ�� �ϰ� �� �����̳ʿ� ���ͷ����͸� �����Ͽ� ���� find, sort, ...�� ������ ��