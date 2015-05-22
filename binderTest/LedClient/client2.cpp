#include <iostream>
#include "..\io_ipc.h"
using namespace std;

// step2. ���δ� ���� ���� Ŭ������ 2�� �̻��� ��ü�� ������ ������ ����
// -> �̱��� ���·� ����
class ProcessState {
	int mDriverFD;

	// 1. �����ڴ� private ������ ����
	ProcessState() : mDriverFD(open_driver()) {}
	static ProcessState* pInstance;

	// 3. ����� ������ �����ϱ� ���� ���� �����ڿ� ���� ������ �Լ��� private ������ ���� (������ ���ص���)
	ProcessState(const ProcessState&);
	void operator = (const ProcessState&);

public:
	// 2. ������ ��ü�� ��ȯ�ϱ� ���� ���� �������̽��� ����
	//static ProcessState& getInstance() { return pInstance; }
	static ProcessState* self() {
		if (pInstance == 0)
			pInstance = new ProcessState;
		return pInstance;
	}
	
	int getDriver() const { return mDriverFD; }
	int open_driver() { return binder_open(128 * 1024); }
};
ProcessState* ProcessState::pInstance = 0;

int main()
{
	//ProcessState* proc(new ProcessState);	// ������ �޸� �Ҵ� �Ǹ� ���� -> �̱��� ���·� ������
	ProcessState* proc(ProcessState::self());

	int msg, reply;

	int handle = binder_call(proc->getDriver(),
		(int*)"LedService",
		&reply,
		BINDER_SERVICE_MANAGER,
		SVC_MGR_CHECK_SERVICE);
	while (1)
	{
		getchar(); binder_call(proc->getDriver(), &msg, &reply, handle, 1);
		getchar(); binder_call(proc->getDriver(), &msg, &reply, handle, 2);
	}

	return 0;
}