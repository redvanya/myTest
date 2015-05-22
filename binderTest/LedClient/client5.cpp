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

// step 5. 서비스의 핸들을 보관 및 관리하는 클래스를 도입한다
class BpBinder {
	int mHandle;
public:
	BpBinder(int handle) : mHandle(handle) {}

	int transact(int code, int *msg, int * reply) {
		return IPCThreadState::self()->transact(mHandle, code, msg, reply);
	}
};
int main()
{
	ProcessState* proc(ProcessState::self());

	int msg, reply;

	int handle = binder_call(proc->getDriver(),
		(int*)"LedService",
		&reply,
		BINDER_SERVICE_MANAGER,
		SVC_MGR_CHECK_SERVICE);
	//handle = -1;	// 이렇게 되면 ERROR. -> 클래스를 도입하고 안전하게 보관하자

	// 이제 핸들을 생성하고 관리하는 객체를 생성한다
	BpBinder* binder(new BpBinder(handle));

	while (1)
	{
		//getchar(); IPCThreadState::self()->transact(handle, 1, &msg, &reply);	// 항상 handle을 첫번째 인자로 가지고 있으니, 멤버 변수로 가지자
		//getchar(); IPCThreadState::self()->transact(handle, 2, &msg, &reply);
		getchar(); binder->transact(1, &msg, &reply);
		getchar(); binder->transact(2, &msg, &reply);
	}

	return 0;
}