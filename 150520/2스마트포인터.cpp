#include <iostream>
using namespace std;

#if 0
class Car {
public:
	Car() { cout << "Car()" << endl; }
	~Car() { cout << "~Car()" << endl; }

	void go() { cout << "go! go! go!" << endl; }
};

void main() {
	{
		// �� ��ü�� �Ҹ��ڰ� ȣ��Ǵ� ������ delete �����ڸ� ���
		// ��, delete ������ ���� ���� ��� ��ü�� ������ ���� ����
		// -> �޸� ���� ���� (memory leak)
		Car* pCar = new Car;	// ���� ������ ��ü�� ��������� �Ҹ��ڸ� �ҷ���� �Ѵ�.
		// delete pCar;
		// �޸� ���� �߻�
	}
	getchar();
}

//void main() {
//	// ���� ������ ����
//	{
//		Car c;	// ���� ��ü and �ڵ� ����
//				// ���� ��ü�� �޸𸮰� �ڵ����� �����ǰ� �����ڰ� ȣ��ȴ�
//				// ���� ��ü�� �Ҹ��ڴ� ��ü�� ���ÿ��� �ı��� �� ȣ��
//	}
//	getchar();
//}
#endif

#if 0
class Car {
public:
	Car() { cout << "Car()" << endl; }
	~Car() { cout << "~Car()" << endl; }

	void go() { cout << "go! go! go!" << endl; }
};

// �ڿ� ������ ���� Ŭ������ �����غ��ô� : �Ҹ��ڸ� Ȱ���� �ڿ��� ����
// ��ü�� ������ ������ �ϴ� ���� ����Ʈ�����Ͷ� �Ѵ�
class Sptr {
	Car* pObj;
public:
	Sptr(Car* p) : pObj(p) {}
	~Sptr() { delete pObj; }

	Car* operator->() { return pObj; }
	Car& operator*() { return *pObj; }	// Car�� �����ϸ� �ӽð�ü�� �����Ǿ� �Ҹ��ڰ� �ι� �Ҹ�. �����ڷ� �����ϱ�
};

void main() {
	{
		//Car* pCar = new Car;	// �Ҹ��� �ȺҸ�
		Sptr pCar = new Car;	// �Ҹ��� �Ҹ�
		pCar->go();		// garbage collector�� ���������� ���� ������ó�� �������� �ʴ´� -> ������ �����ε� "->" �ʿ�
						// pCar.operator->()go(); : ������ ���� -> (pCar.operator->())->go(); ������ ����
		(*pCar).go();		// pCar.operator*().go(); ������ �켱������ . > * �̱� ������ ()�� �����ش�
	}
	getchar();
}
#endif

class Car {
public:
	Car() { cout << "Car()" << endl; }
	~Car() { cout << "~Car()" << endl; }

	void go() { cout << "go! go! go!" << endl; }
};

// ����Ʈ �����Ͷ� ������ ��ü�� �ٸ� Ÿ���� ������ ������ �ϴ°�
template <typename T>
class Sptr {
	T* pObj;
public:
	Sptr(T* p) : pObj(p) {}
	~Sptr() { delete pObj; }

	// ����Ʈ �����ʹ� �Ʒ��� �� �����ڸ� ������ �ؾ��Ѵ�
	T* operator->() { return pObj; }
	T& operator*() { return *pObj; }
};

// ����Ʈ �����ʹ� ��¥ �����Ͱ� �ƴ� ��ü�̹Ƿ� ����ڰ� ��ü�� ����/����/����/�Ҹ��� ������ ������ �� �ִ�.
// ��ǥ���� Ȱ�� ��) �Ҹ��ڸ� ����� �ڵ� ����
void main() {
	{
		Sptr<Car> pCar = new Car;
		pCar->go();
		(*pCar).go();
	}
	getchar();
}