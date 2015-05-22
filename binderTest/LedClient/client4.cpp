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

// step 3. 바인더와 통신을 하기 위한 클래스를 도입한다
// binder_call 함수의 사용이 어렵기 때문
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
int main()
{
	ProcessState* proc(ProcessState::self());
	//IPCThreadState* ipc(new IPCThreadState);
	//IPCThreadState* ipc(IPCThreadState::self());	// Android Framework에서는 포인터 선언 없이 바로 씀 (아래)

	int msg, reply;

	int handle = binder_call(proc->getDriver(),
		(int*)"LedService",
		&reply,
		BINDER_SERVICE_MANAGER,
		SVC_MGR_CHECK_SERVICE);
	while (1)
	{
		//getchar(); ipc->transact(handle, 1, &msg, &reply);
		//getchar(); ipc->transact(handle, 2, &msg, &reply);
		getchar(); IPCThreadState::self()->transact(handle, 1, &msg, &reply);
		getchar(); IPCThreadState::self()->transact(handle, 2, &msg, &reply);
	}

	return 0;
}