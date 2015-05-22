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

// 위의 코드는 안드로이드 프레임워크가 제공하는 코드입니다
//----------------------------------------------------------------
// 아래의 코드느 서비스 제작자가 구현하는 코드입니다

// step 10. 프록시와 서비스가 반드시 구현해야 할 함수를 정의하기 위하여 인터페이스 도입
class ILedService {
public:
	virtual void ledOn() = 0;
	virtual void ledOff() = 0;
	// 1. IBinder 타입을 자신의 타입으로 변환하는 함수를 제공해야 합니다
	// 이때 함수는 선언만 합니다
	static ILedService* asInterface(IBinder* p);

	// 2. asBinder를 순수 가상 함수로 제공해야 합니다
//protected:	// 원래 protected로 해야한다
	virtual IBinder* onAsBinder() = 0;
	IBinder* asBinder() {
		return this ? onAsBinder() : 0;
	}
};

// 이제 프록시 설계자는 BpRefBase 클래스 분만 아니라 ILedService 클래스도 상속받는 규칙이 생김
class BpLedService : public BpRefBase, public ILedService {
	int msg, reply;
public:
	BpLedService(IBinder* p) : BpRefBase(p) {}
	void ledOn() { remote()->transact(1, &msg, &reply); }
	void ledOff() { remote()->transact(2, &msg, &reply); }

	IBinder* onAsBinder(){ return remote(); }
};

// 프록시 설계자는 아래의 함수를 구현해야 하는 규칙이 발생한다
ILedService* ILedService::asInterface(IBinder* p){
	return new BpLedService(p);
}

int main()
{
	IBinder* binder = getService("LedService");
	//BpLedService* ledService = new BpLedService(binder);	// BpLedService로 하면 BpRefBase의 remote()가 노출된다.
	//ILedService* ledService = new BpLedService(binder);	//BpLedService 이걸 몰라도 asInterface에 binder만 넣으면 되도록 하기
	// ILedService* ledService = ILedService*(new BpLedService(binder)); -> 이렇게 해도 BpLedService가 노출된다. 함수로 래핑해야..!
	ILedService* ledService = ILedService::asInterface(binder);

	while (1)
	{
		getchar(); ledService->ledOn();
		getchar(); ledService->ledOff();
	}
	return 0;
}