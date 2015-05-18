// windows thread api
#include <stdio.h>
#include <Windows.h>

#if 0
unsigned long __stdcall thread_main(void* arg) {
	const char* s = static_cast<const char*>(arg);

	for (int i = 0; i < 10; i++) {
		printf("%s\n", s);
		Sleep(1000);
	}
	return 0;
}

void main() {
	CreateThread(0, 0, thread_main/* �Ϲ��Լ� - call back �Լ� */, "hello", 0, 0);
	// C���� callback�Լ��� �θ����� �Լ� �����͸� ���
	// C++������ �����Լ��� ��� ����
	getchar();
}
#endif

class Thread {
	//static Thread* self;	// ��Ƽ �����忡�� ���� ������ ����ϸ� �����忡 safety���� �ʴ�. (�ܺο��� ���� ����) -> ����ȭ ��ü�� �������(mutex), ���������� ����ϴ���
protected:
	virtual unsigned long threadMain() { return 0; }
public:
	static unsigned long __stdcall __threadMain(void *arg) {	// ��� �Լ��̱� ������ �Ϲ� �Լ�ó�� �ǵ��� static�� ���ش�
		//threadMain();	// ���⼭�� this�� ���� ������ ȣ���� �ȵ�. this�� ��򰡿� ��������� ��.
		//Thread* self = (Thread*)(arg);	// �̷��� casting �ϸ� �ȵ�. type checking�� ����.
		Thread* self = static_cast<Thread*>(arg);
		self->threadMain();
		return 0;
	}
	void start() {	//void start(Thread* const this)
		//self = this;	// �ڱ� �ڽ��� �����͸� ��Ҵ�
		CreateThread(0, 0, __threadMain, this, 0, 0);
	}
};
//Thread* Thread::self = 0;

class FileDownThread : public Thread {
public:
	unsigned long threadMain() {
		for (int i = 0; i <= 10; i++) {
			system("cls");
			printf("%d %% downloading...\n", i * 10);
			Sleep(1000);
		}
		printf("completed!\n");
		return 0;
	}
};

void main() {
	FileDownThread t;
	t.start();
	getchar();
}