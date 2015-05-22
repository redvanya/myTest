#include "../Android.h"

// �ȵ���̵尡 �����ϴ� �ڵ带 ��� Android.h�� �ٿ��ֽ��ϴ�.

class LedService : public BnInterface<ILedService> {
public:
	void ledOn() { cout << "LED ON" << endl; }
	void ledOff() { cout << "LED OFF" << endl; }

	int onTransact(int code, int* msg, int* reply) {
		switch (code) {
		case 1: ledOn(); break;
		case 2: ledOff(); break;
		}
		return 0;
	}
};



int main()
{
	// 1. ���δ� ����̹� ����
	// struct binder_state* bs;
	//int fd = binder_open(128 * 1024); // 128KB: ���Ź���
	ProcessState* proc = ProcessState::self();

	// 2. ���� �Ŵ������� ���� �̸� ���
	//int reply;
	//binder_call(fd,
	//	(int*)"LedService",
	//	&reply,
	//	BINDER_SERVICE_MANAGER,	//0�� ����
	//	SVC_MGR_ADD_SERVICE);	// RPC �ڵ�

	// defaultServiceManager()->addService(String16("LedService"), new LedService);
	addService("LedService", new LedService);

	// 3. Ŭ���̾�Ʈ�� ��û ���
	//binder_loop(fd, myHandler);
	IPCThreadState::self()->joinThreadPool();
	return 0;
}