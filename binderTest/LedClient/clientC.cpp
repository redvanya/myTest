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

class BpRefBase {
	IBinder* mRemote;
public:
	BpRefBase(IBinder* p) : mRemote(p) {}
	IBinder* remote() { return mRemote; }
};

template<typename INTERFACE> INTERFACE* interface_cast(IBinder* p) {
	return INTERFACE::asInterface(p);
}

template<typename INTERFACE>
class BpInterface : public BpRefBase, public INTERFACE {
public:
	BpInterface(IBinder* p) : BpRefBase(p) {}
	IBinder* onAsBinder(){ return remote(); }
};

// step 12. 인터페이스 클래스의 설계를 도와줄 헬퍼 클래스를 도입합니다.
class IInterface {
protected:
	virtual IBinder* onAsBinder() = 0;
public:
	IBinder* asBinder() {
		return this ? onAsBinder() : 0;
	}
};

// 위의 코드는 안드로이드 프레임워크가 제공하는 코드입니다
//----------------------------------------------------------------
// 아래의 코드는 서비스 제작자가 구현하는 코드입니다

// 인터페이스 설계자는 IInterface클래스를 상속받기로 약속합니다.
class ILedService : public IInterface {
public:
	virtual void ledOn() = 0;
	virtual void ledOff() = 0;
	static ILedService* asInterface(IBinder* p);
};

class BpLedService : public BpInterface<ILedService> {
	int msg, reply;
public:
	BpLedService(IBinder* p) : BpInterface<ILedService>(p) {}
	void ledOn() { remote()->transact(1, &msg, &reply); }
	void ledOff() { remote()->transact(2, &msg, &reply); }
};

ILedService* ILedService::asInterface(IBinder* p){
	return new BpLedService(p);
}

int main()
{
	IBinder* binder = getService("LedService");
	ILedService* ledService = interface_cast<ILedService>(binder);

	while (1)
	{
		getchar(); ledService->ledOn();
		getchar(); ledService->ledOff();
	}
	return 0;
}