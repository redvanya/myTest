
#include <iostream>
#include "..\io_ipc.h"
using namespace std;

class ProcessState
{
	int mDriverFD;
	ProcessState() : mDriverFD(open_driver()) {}
	ProcessState(const ProcessState&);
	void operator=(const ProcessState&);

	static ProcessState* pInstance;

public:
	static ProcessState* self()
	{
		if (pInstance == 0)
			pInstance = new ProcessState;
		return pInstance;
	}

	int getDriver() { return mDriverFD; }
	int open_driver() { return binder_open(128 * 1024); }
};
ProcessState* ProcessState::pInstance = 0;

class IPCThreadState
{
	ProcessState* mProcess;

	IPCThreadState() : mProcess(ProcessState::self()) {}
	IPCThreadState(const IPCThreadState&);
	void operator=(const IPCThreadState&);

	static IPCThreadState* pInstance;

public:
	static IPCThreadState* self()
	{
		if (pInstance == 0)
			pInstance = new IPCThreadState;
		return pInstance;
	}

	int transact(int handle, int code, int* msg, int* reply)
	{
		int driver = mProcess->getDriver();
		return binder_call(driver, msg, reply, handle, code);
	}
};
IPCThreadState* IPCThreadState::pInstance = 0;

class IBinder
{
public:
	virtual int transact(int code, int* msg, int* reply) = 0;
};

class BpBinder : public IBinder
{
	int mHandle;
public:
	BpBinder(int handle) : mHandle(handle) {}
	int transact(int code, int* msg, int* reply) {
		return IPCThreadState::self()->transact(mHandle, code, msg, reply);
	}
};

IBinder* getService(const char* name)
{
	int reply;
	int handle = binder_call(ProcessState::self()->getDriver(),
		(int*)name,
		&reply,
		BINDER_SERVICE_MANAGER,
		SVC_MGR_CHECK_SERVICE);

	return new BpBinder(handle);	// return handle;
}

// step 8. ���� �ѹ��� �Լ� ȣ���� �������̽��� �����ϱ� ���Ͽ�
// �Ʒ��� Ŭ������ �����մϴ�.

// �л� �ý��ۿ��� ������ ����� ���� �����ϴ� ���� �ƴ϶� ������ �����
// ��� ��û�ϴ� ������ ���Ͻ�(proxy)��� �մϴ�. �ȵ���̵� �����ӿ�ũ������
// �Ϲ� Ŭ������ ���Ͻ� Ŭ������ �����ϱ� ���Ͽ� ���ξ�� Bp(Binder Proxy)��
// ����մϴ�.
class BpLedService	// class LedService
{
	IBinder* mRemote;
	int msg, reply;

public:
	BpLedService(IBinder* p) : mRemote(p) {}

	// RPC CODE -> INTERFACE
	void ledOn() { mRemote->transact(1, &msg, &reply); }
	void ledOff() { mRemote->transact(2, &msg, &reply); }
};

int main()
{
	ProcessState* proc(ProcessState::self());
	IBinder* binder = getService("LedService");
	BpLedService* ledService = new BpLedService(binder);
	
	while (1)
	{
		int msg, reply;
		getchar(); ledService->ledOn();		// getchar(); binder->transact(1, &msg, &reply);
		getchar(); ledService->ledOff();	// getchar(); binder->transact(2, &msg, &reply);
	}
	return 0;
}