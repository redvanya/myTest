
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

	return new BpBinder(handle);
}

class BpRefBase
{
	IBinder* mRemote;

public:
	IBinder* remote() { return mRemote; }
	BpRefBase(IBinder* p) : mRemote(p) {}
};

// 아래의 코드는 안드로이드 프레임워크가 제공하는 코드입니다.
//--------------------------------------------------------------------------------------
// 아래의 코드는 서비스 제작자가 구현하는 코드입니다.

// step 10. 프록시와 서비스가 반드시 구현해야 할 함수를 정의하기 위하여
// 인터페이스를 도입합니다.
class ILedService
{
public:
	virtual void ledOn() = 0;
	virtual void ledOff() = 0;

	// 1. IBinder 타입을 자신의 타입으로 변환하는 함수를 제공해야 합니다.
	// 이 때 함수는 선언만 합니다.
	static ILedService* asInterface(IBinder* p);

	// 2. asBinderAC를 순수 가상 함수로 제공해야 합니다.
	IBinder* asBinder() { return this ? onAsBinder() : 0; }
	virtual IBinder* onAsBinder() = 0;
};

// 이제 프록시 설계자는 BpRefBase 클래스 뿐만 아니라 ILedService 클래스도
// 상속받아야 하는 규칙이 발생합니다.
class BpLedService : public BpRefBase, public ILedService
{
	int msg, reply;

public:
	IBinder* onAsBinder() { return remote(); }


	BpLedService(IBinder* p) : BpRefBase(p) {}
	void ledOn() { remote()->transact(1, &msg, &reply); }
	void ledOff() { remote()->transact(2, &msg, &reply); }
};
// 프록시 설계자는 아래의 함수를 구현해야 하는 규칙이 발생합니다.
ILedService* ILedService::asInterface(IBinder* p)
{
	return new BpLedService(p);
}



int main()
{
	ProcessState* proc(ProcessState::self());
	IBinder* binder = getService("LedService");
	// BpLedService* ledService = new BpLedService(binder);
	// ILedService* ledService = new BpLedService(binder);
	// ILedService* ledService = ILedService*(new BpLedService(binder));
	ILedService* ledService = ILedService::asInterface(binder);

	while (1)
	{
		getchar(); ledService->ledOn();
		getchar(); ledService->ledOff();
	}
	return 0;
}