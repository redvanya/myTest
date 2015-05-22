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

class IBinder {
public:
	virtual int transact(int code, int *msg, int * reply) = 0;
};

// addService함수 위의 IBinder 타입의 포인터를 아래에 복사한다
IBinder* service;
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

	//------------------------------------------------------------------
	// binder_loop의 실제 함수는 다음의 코드 입니다.
	void joinThreadPool(){
		// 아래의 함수는 C 언어의 함수이므로 C 함수의 포인터만 등록된다.
		binder_loop(mProcess->getDriver(), myHandler);
	}
	// 그래서 아래의 함수를 정적 멤버 함수로 만들고 등록한다.
	// 정적 멤버 함수는 일반 멤버 함수 포인터에 저장될 수 있기 때문이다
	static int myHandler(int code, int* msg, int* reply) {
		return service->transact(code, msg, reply);
	}
};
IPCThreadState* IPCThreadState::pInstance = 0;

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

#define DECLARE_META_INTERFACE(INTERFACE)	\
	static INTERFACE* asInterface(IBinder* p);

#define IMPLEMENT_META_INTERFACE(INTERFACE)		\
	I##INTERFACE* I##INTERFACE::asInterface(IBinder* p){ return new Bp##INTERFACE(p); }	// ##: 매크로에서 두 문자열 이어줌

class BBinder : public IBinder {
protected:
	int transact(int code, int* msg, int* reply) {
		return onTransact(code, msg, reply);
	}
public:
	virtual int onTransact(int code, int* msg, int* reply) { return 0; }
};

template<typename INTERFACE>
class BnInterface : public BBinder, public INTERFACE {
public:
	IBinder* onAsBinder() { return this; }
};

// step 4. 서비스 등록을 위한 함수를 구현합니다.
void addService(const char* name, BBinder* p){
	service = p;	// 실제 서비스 객체의 주소는 바인더 드라이버 내부에 저장된다.
	int reply;
	binder_call(ProcessState::self()->getDriver(),
		(int*)name,
		&reply,
		BINDER_SERVICE_MANAGER,	//0번 서비스
		SVC_MGR_ADD_SERVICE);	// RPC 코드
}

// 위의 코드는 안드로이드 프레임워크가 제공하는 코드입니다
//----------------------------------------------------------------
// 아래의 코드는 서비스 제작자가 구현하는 코드입니다

// 인터페이스 설계자는 IInterface클래스를 상속받기로 약속합니다.
class ILedService : public IInterface {
public:
	virtual void ledOn() = 0;
	virtual void ledOff() = 0;
	//static ILedService* asInterface(IBinder* p);
	DECLARE_META_INTERFACE(ILedService)
};