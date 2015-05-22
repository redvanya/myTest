
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

template<typename INTERFACE> INTERFACE* interface_cast(IBinder* p)
{
	return INTERFACE::asInterface(p);
}

// step 11. 다중 상속을 단일 상속으로 변경하기 위해 아래의 클래스를 도입합니다.
template<typename INTERFACE>
class BpInterface : public BpRefBase, public INTERFACE
{
public:
	BpInterface(IBinder* p) : BpRefBase(p) {}
	IBinder* onAsBinder() { return remote(); }
};

// 위의 코드는 안드로이드 프레임워크가 제공하는 코드입니다.
//--------------------------------------------------------------------------------------
// 아래의 코드는 서비스 제작자가 구현하는 코드입니다.

class ILedService
{
public:
	virtual void ledOn() = 0;
	virtual void ledOff() = 0;
	static ILedService* asInterface(IBinder* p);
	IBinder* asBinder() { return this ? onAsBinder() : 0; }
	virtual IBinder* onAsBinder() = 0;
};



// 프록시를 설계자는 BpInterface 클래스를 상속받는 규칙이 발생합니다.
// class BpLedService : public BpRefBase, public ILedService
class BpLedService : public BpInterface<ILedService>	// CRTP
{
	int msg, reply;
public:
	// IBinder* onAsBinder() { return remote(); }
	BpLedService(IBinder* p) : BpInterface(p) {}
	void ledOn() { remote()->transact(1, &msg, &reply); }
	void ledOff() { remote()->transact(2, &msg, &reply); }
};

ILedService* ILedService::asInterface(IBinder* p)
{
	return new BpLedService(p);
}

int main()
{
	ProcessState* proc(ProcessState::self());
	IBinder* binder = getService("LedService");
	// ILedService* ledService = ILedService::asInterface(binder);
	ILedService* ledService = interface_cast<ILedService>(binder);

	while (1)
	{
		getchar(); ledService->ledOn();
		getchar(); ledService->ledOff();
	}
	return 0;
}