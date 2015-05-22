
#include "../Android.h"


//------------------------------------------------------------------------
// �Ʒ��� �ڵ�� ���� �����ڰ� �����ϴ� �ڵ��Դϴ�.

// �ȵ���̵尡 �����ϴ� �ڵ带 ��� Android.h ���Ͽ� �ٿ���������

class LedService : public BnInterface<ILedService>
{
public:
	void ledOn() { cout << "LED ON" << endl; }
	void ledOff() { cout << "LED OFF" << endl; }

	int onTransact(int code, int* msg, int* reply)
	{
		switch (code)
		{
		case 1: ledOn(); break;
		case 2: ledOff(); break;
		}
		return 0;
	}
};



int main()
{
	ProcessState* proc(ProcessState::self());

	// 2. ���� �Ŵ������� ���� �̸� ���
	//int reply;
	//binder_call(fd,
	//	(int*)"LedService",
	//	&reply,
	//	BINDER_SERVICE_MANAGER,
	//	SVC_MGR_ADD_SERVICE);
	
	// defaultServiceManager()->addService(String16("LedService"), new LedService);
	addService("LedService", new LedService);


	// 3. Ŭ���̾�Ʈ�� ��û ���
	// binder_loop(fd, myHandler);
	IPCThreadState::self()->joinThreadPool();
	return 0;
}