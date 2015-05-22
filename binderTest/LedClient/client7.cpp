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

// step 7. 핸들을 관리하는 모든 클래스를 하나의 타입으로 처리하기 위하여 부모 클래스(상속)을 도입한다
// 순수 가상 함수를 1개 이상 가지고 있는 클래스는 인터페이스이다. 관례적으로 I를 접두사로 붙인다.
class IBinder {
public:
	virtual int transact(int code, int *msg, int * reply) = 0;	// 자식이 반드시 구현하도록 하기 위해서 순수 가상 함수로 만든다
};

// 이제 핸들을 관리하는 클래스들은 IBinder 클래스를 상속 받기로 약속한다.
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