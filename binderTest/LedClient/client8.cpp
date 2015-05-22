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

	return new BpBinder(handle);	// return handle;
}

// step 8. 매직 넘버를 함수 호출의 인터페이스로 변경하기 위하여 아래의 클래스를 도입한다
// 프록시(proxy): 분산 시스템에서 서비스의 기능을 직접 제공하는 것이 아니라 서비스의 기능을 대신 요청하는 개념
// 안드로이드 프레임워크에서는 일반 클래스와 프록시 클래스를 구분하기 위하여 접두어로 Bp(Binder Proxy)를 쓴다
class BpLedService {
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
	IBinder* binder = getService("LedService");
	// proxy : 대신 처리해주는 것
	// Android Framework에서는 접두어로 Bp를 쓴다. 실제 서비스를 요청해주는 서비스
	BpLedService* ledService = new BpLedService(binder);

	while (1)
	{
		int msg, reply;
		// 1? 2? 뭔지 알 수 없다. -> 매크로 상수, 심볼릭 상수 등으로 변경 가능
		// 여기서는 LedOn, LedOff와 같은 함수로 대체 가능
		//getchar(); binder->transact(1, &msg, &reply);
		//getchar(); binder->transact(2, &msg, &reply);
		getchar(); ledService->ledOn();
		getchar(); ledService->ledOff();
	}
	return 0;
}