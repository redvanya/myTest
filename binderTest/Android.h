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

// addService�Լ� ���� IBinder Ÿ���� �����͸� �Ʒ��� �����Ѵ�
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
	// binder_loop�� ���� �Լ��� ������ �ڵ� �Դϴ�.
	void joinThreadPool(){
		// �Ʒ��� �Լ��� C ����� �Լ��̹Ƿ� C �Լ��� �����͸� ��ϵȴ�.
		binder_loop(mProcess->getDriver(), myHandler);
	}
	// �׷��� �Ʒ��� �Լ��� ���� ��� �Լ��� ����� ����Ѵ�.
	// ���� ��� �Լ��� �Ϲ� ��� �Լ� �����Ϳ� ����� �� �ֱ� �����̴�
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

// step 12. �������̽� Ŭ������ ���踦 ������ ���� Ŭ������ �����մϴ�.
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
	I##INTERFACE* I##INTERFACE::asInterface(IBinder* p){ return new Bp##INTERFACE(p); }	// ##: ��ũ�ο��� �� ���ڿ� �̾���

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

// step 4. ���� ����� ���� �Լ��� �����մϴ�.
void addService(const char* name, BBinder* p){
	service = p;	// ���� ���� ��ü�� �ּҴ� ���δ� ����̹� ���ο� ����ȴ�.
	int reply;
	binder_call(ProcessState::self()->getDriver(),
		(int*)name,
		&reply,
		BINDER_SERVICE_MANAGER,	//0�� ����
		SVC_MGR_ADD_SERVICE);	// RPC �ڵ�
}

// ���� �ڵ�� �ȵ���̵� �����ӿ�ũ�� �����ϴ� �ڵ��Դϴ�
//----------------------------------------------------------------
// �Ʒ��� �ڵ�� ���� �����ڰ� �����ϴ� �ڵ��Դϴ�

// �������̽� �����ڴ� IInterfaceŬ������ ��ӹޱ�� ����մϴ�.
class ILedService : public IInterface {
public:
	virtual void ledOn() = 0;
	virtual void ledOff() = 0;
	//static ILedService* asInterface(IBinder* p);
	DECLARE_META_INTERFACE(ILedService)
};