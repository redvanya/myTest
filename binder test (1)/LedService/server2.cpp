
#include "../Android.h"

class BBinder : public IBinder
{
protected:
	// ���� �ݹ��� ����ڰ� ���� �������̵� �ϴ� ���� ���� ���ϹǷ�
	// �ܺ� �ݹ� �������̽��� onTransact�� �����մϴ�.
	int transact(int code, int* msg, int* reply){
		return onTransact(code, msg, reply);
	}

public:
	virtual int onTransact(int code, int* msg, int* reply) { return 0; }
};

// step 2. ���� �����ڴ� �������̽��� ��ӹ����� �˴ϴ�.
class LedService : public BBinder, public ILedService
{
public:
	// IInteface�� onAsBinder�� �����ؾ� �մϴ�.
	IBinder* onAsBinder() { return this; }

	// ILedService�� �������̽��� �����մϴ�.
	void ledOn() { cout << "LED ON" << endl; }
	void ledOff() { cout << "LED OFF" << endl; }

	// int myHandler(int code, int* msg, int* reply)
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
	// 1. ���δ� ����̹� ����
	// struct binder_state* bs;
	int fd = binder_open(128 * 1024); // 128KB

	// 2. ���� �Ŵ������� ���� �̸� ���
	int reply;
	binder_call(fd,
		(int*)"LedService",
		&reply,
		BINDER_SERVICE_MANAGER,
		SVC_MGR_ADD_SERVICE);

	// 3. Ŭ���̾�Ʈ�� ��û ���
	binder_loop(fd, myHandler);
	return 0;
}