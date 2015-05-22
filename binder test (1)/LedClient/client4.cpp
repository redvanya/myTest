
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


// step 4. 아래의 클래스를 싱글톤 형태로 구현해 보세요 :D
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

int main()
{
	ProcessState* proc(ProcessState::self());
	// IPCThreadState* ipc(IPCThreadState::self());	// IPCThreadState* ipc(new IPCThreadState);

	int msg, reply;
	int handle = binder_call(proc->getDriver(),
		(int*)"LedService",
		&reply,
		BINDER_SERVICE_MANAGER,
		SVC_MGR_CHECK_SERVICE);

	while (1)
	{
		// getchar(); ipc->transact(handle, 1, &msg, &reply);
		getchar(); IPCThreadState::self()->transact(handle, 1, &msg, &reply);

		// getchar(); ipc->transact(handle, 2, &msg, &reply);
		getchar(); IPCThreadState::self()->transact(handle, 2, &msg, &reply);

	}
	return 0;
}