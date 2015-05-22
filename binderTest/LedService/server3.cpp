#include "../Android.h"

class BBinder : public IBinder {
protected:
	int transact(int code, int* msg, int* reply) {
		return onTransact(code, msg, reply);
	}
public:
	virtual int onTransact(int code, int* msg, int* reply) { return 0; }
};

// step 3. ���� ����� ���� ������� �����ϱ� ���� �Ʒ��� Ŭ������ �����Ѵ�.
template<typename INTERFACE>
class BnInterface : public BBinder, public INTERFACE {
public:
	IBinder* onAsBinder() { return this; }
};

// ���� ���� �����ڴ� BnInterface�� ����ϱ�� ����մϴ�.
//class LedService : public BBinder, public ILedService {	// ���� ��� �߻�
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
	int fd = binder_open(128 * 1024); // 128KB: ���Ź���

	// 2. ���� �Ŵ������� ���� �̸� ���
	int reply;
	binder_call(fd,
		(int*)"LedService",
		&reply,
		BINDER_SERVICE_MANAGER,	//0�� ����
		SVC_MGR_ADD_SERVICE);	// RPC �ڵ�

	// 3. Ŭ���̾�Ʈ�� ��û ���
	binder_loop(fd, myHandler);
	return 0;
}