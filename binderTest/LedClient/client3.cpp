#include <iostream>
#include "..\io_ipc.h"
using namespace std;

// step2. ���δ� ���� ���� Ŭ������ 2�� �̻��� ��ü�� ������ ������ ����
// -> �̱��� ���·� ����
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

// step 3. ���δ��� ����� �ϱ� ���� Ŭ������ �����Ѵ�
// binder_call �Լ��� ����� ��Ʊ� ����
class IPCThreadState {
	ProcessState* mProcess;
public:
	IPCThreadState() : mProcess(ProcessState::self()) {}	// �̱����� ����: ��𼭵� self�� ���� ���� (static�̴ϱ�)
	// �Ʒ��� �Լ��� binder_call�� ���� �Լ� �Դϴ�.
	int transact(int handle, int code, int* msg, int* reply) {
		int driver = mProcess->getDriver();
		return binder_call(driver, msg, reply, handle, code);
	}
};

int main()
{
	ProcessState* proc(ProcessState::self());
	IPCThreadState* ipc(new IPCThreadState);	// �̰͵� �̱������� ���� �ʿ�

	int msg, reply;

	int handle = binder_call(proc->getDriver(),
							(int*)"LedService",
							&reply,
							BINDER_SERVICE_MANAGER,
							SVC_MGR_CHECK_SERVICE);
	while (1)
	{	// binder_call : ���� ���δ� ������ ��/���� �Ѵ� (���)
		//getchar(); binder_call(proc->getDriver(), &msg, &reply, handle, 1);
		//getchar(); binder_call(proc->getDriver(), &msg, &reply, handle, 2);
		getchar(); ipc->transact(handle, 1, &msg, &reply);
		getchar(); ipc->transact(handle, 2, &msg, &reply);
	}

	return 0;
}