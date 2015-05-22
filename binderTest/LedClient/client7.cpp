#include <iostream>
#include "..\io_ipc.h"
using namespace std;

class ProcessState {
	int mDriverFD;
	static ProcessState* pInstance;

	ProcessState() : mDriverFD(open_driver()) {}
	ProcessState(const ProcessState&);
	void operator = (const ProcessState&);
public:
	static ProcessState* self() {
		if (pInstance == 0)
			pInstance = new ProcessState;
		return pInstance;
	}
	int getDriver() const { return mDriverFD; }
	int open_driver() { return binder_open(128 * 1024); }
};
ProcessState* ProcessState::pInstance = 0;

class IPCThreadState {
	ProcessState* mProcess;
	static IPCThreadState* pInstance;

	IPCThreadState() : mProcess(ProcessState::self()) {}
	IPCThreadState(const IPCThreadState&);
	void operator = (const IPCThreadState&);
public:
	static IPCThreadState* self() {
		if (pInstance == 0)
			pInstance = new IPCThreadState;
		return pInstance;
	}
	int transact(int handle, int code, int* msg, int* reply) {
		int driver = mProcess->getDriver();
		return binder_call(driver, msg, reply, handle, code);
	}
};
IPCThreadState* IPCThreadState::pInstance = 0;

// step 7. �ڵ��� �����ϴ� ��� Ŭ������ �ϳ��� Ÿ������ ó���ϱ� ���Ͽ� �θ� Ŭ����(���)�� �����Ѵ�
// ���� ���� �Լ��� 1�� �̻� ������ �ִ� Ŭ������ �������̽��̴�. ���������� I�� ���λ�� ���δ�.
class IBinder {
public:
	virtual int transact(int code, int *msg, int * reply) = 0;	// �ڽ��� �ݵ�� �����ϵ��� �ϱ� ���ؼ� ���� ���� �Լ��� �����
};

// ���� �ڵ��� �����ϴ� Ŭ�������� IBinder Ŭ������ ��� �ޱ�� ����Ѵ�.
class BpBinder : public IBinder {
	int mHandle;
public:
	BpBinder(int handle) : mHandle(handle) {}

	int transact(int code, int *msg, int * reply) {
		return IPCThreadState::self()->transact(mHandle, code, msg, reply);
	}
};

//int getService(const char* name) {
//BpBinder* getService(const char* name) {
IBinder* getService(const char* name) {
	int reply;
	int handle = binder_call(ProcessState::self()->getDriver(),
		(int*)name,
		&reply,
		BINDER_SERVICE_MANAGER,
		SVC_MGR_CHECK_SERVICE);

	return new BpBinder(handle);	// return handle;
}

int main()
{
	//int handle = getService("LedService");
	//BpBinder* binder(new BpBinder(handle));
	//BpBinder* binder = getService("LedService");
	IBinder* binder = getService("LedService");

	while (1)
	{
		int msg, reply;
		getchar(); binder->transact(1, &msg, &reply);
		getchar(); binder->transact(2, &msg, &reply);
	}

	return 0;
}