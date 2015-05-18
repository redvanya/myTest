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
	CreateThread(0, 0, thread_main/* 일반함수 - call back 함수 */, "hello", 0, 0);
	// C언어에서 callback함수를 부르려면 함수 포인터를 사용
	// C++에서는 가상함수도 사용 가능
	getchar();
}
#endif

class Thread {
	//static Thread* self;	// 멀티 쓰레드에서 전역 변수를 사용하면 쓰레드에 safety하지 않다. (외부에서 변경 가능) -> 동기화 객체를 만들던가(mutex), 지역변수로 사용하던가
protected:
	virtual unsigned long threadMain() { return 0; }
public:
	static unsigned long __stdcall __threadMain(void *arg) {	// 멤버 함수이기 때문에 일반 함수처럼 되도록 static을 써준다
		//threadMain();	// 여기서는 this가 없기 때문에 호출이 안됨. this를 어딘가에 저장해줘야 함.
		//Thread* self = (Thread*)(arg);	// 이렇게 casting 하면 안됨. type checking이 꺼짐.
		Thread* self = static_cast<Thread*>(arg);
		self->threadMain();
		return 0;
	}
	void start() {	//void start(Thread* const this)
		//self = this;	// 자기 자신의 포인터를 담았다
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