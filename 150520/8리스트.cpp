// 리스트 컨테이너
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

#if 0	// class로 변경하기
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

// 컨테이너 요소를 가리키는 스마트 포인터 설계하기
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

	typedef slist_iterator<T> iterator;	// 사용자가 뽑아쓸 수 있도록, 가져다 쓰는 사람도 쉽고 내부 코드도 간단해 진다
	// 모든 컨테이너 설계자는 컨테이너 내부의 자료구조의 시작과 마지막 다음 위치를 반환하는 함수를 제공하기로 약속한다.
	iterator begin() { return iterator(head); }
	iterator end()   { return iterator(0); }
};

template <typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 ch) {
	while (first != last && *first != ch)	// 여기서 T1은 객체이기 때문에 !=, *, ++ 등이 연산자가 아닌, 함수다. 함수의 호출은 오버헤드가 크다
		++first;							// -> 각 연산자 오버로딩 함수를 인라인으로 바꾸기
	return first;
}

void main() {
	slist<int> s;
	for (int i = 0; i < 10; i++) {
		s.insert_node(i * 10);
	}

	//slist_iterator<int> p1 = xfind(s.begin(), s.end(), 90);	// 사용자가 이터레이터의 심볼명(slist_iterator)을 알아야 한다. -> .h를 통해 확인해야 함
	slist<int>::iterator p1 = xfind(s.begin(), s.end(), 90);
	if (p1 == s.end())	cout << "not found" << endl;
	else	cout << "found" << endl;

	slist<int>::iterator p2;
	for (p2 = s.begin(); p2 != s.end(); p2++){
		cout << *p2 << endl;
	}

	// 아래 vector의 예를 보아도, 컨테이너는 기본적으로 begin, end, iterator 제공
	//vector<int> v;
	//v.begin();
	//v.end();
	//vector<int>::iterator;	
}

// find, sort, ... 를 각 컨테이너 마다 만들고 x 타입까지 하면 무한대
// 그래서 find, sort, ...는 분리하기로 하고 각 컨테이너에 이터레이터를 제공하여 같은 find, sort, ...를 쓰도록 함