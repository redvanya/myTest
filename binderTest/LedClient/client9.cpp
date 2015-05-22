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

class IBinder {
public:
	virtual int transact(int code, int *msg, int * reply) = 0;
};

class BpBinder : public IBinder {
	int mHandle;
public:
	BpBinder(int handle) : mHandle(handle) {}

	int transact(int code, int *msg, int * reply) {
		return IPCThreadState::self()->transact(mHandle, code, msg, reply);
	}
};

IBinder* getService(const char* name) {
	int reply;
	int handle = binder_call(ProcessState::self()->getDriver(),
		(int*)name,
		&reply,
		BINDER_SERVICE_MANAGER,
		SVC_MGR_CHECK_SERVICE);

	return new BpBinder(handle);
}

// step 9. 프록시 설계자가 프록시 구현을 쉽게 할 수 있도록 다음의 클래스를 제공합니다.
class BpRefBase {
	IBinder* mRemote;
public:
	BpRefBase(IBinder* p) : mRemote(p) {}
	IBinder* remote() { return mRemote; }
};

// 이제 프록시 클래스를 설계하는 사람은 BpRefBase 클래스를 상속받기로 약속합니다.
class BpLedService : public BpRefBase {
	int msg, reply;
public:
	BpLedService(IBinder* p) : BpRefBase(p) {}	// 부모의 생성자를 명시적으로 부름	// mRemote(p) {}
	void ledOn() { remote()->transact(1, &msg, &reply); }	// remote()를 통해서 읽어올 수만 있기 때문에 자식에서는 mRemote값을 변경할 수 없다
	void ledOff() { remote()->transact(2, &msg, &reply); }
};

int main()
{
	IBinder* binder = getService("LedService");
	BpLedService* ledService = new BpLedService(binder);

	while (1)
	{
		getchar(); ledService->ledOn();
		getchar(); ledService->ledOff();
	}
	return 0;
}