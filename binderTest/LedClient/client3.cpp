#include <iostream>
#include "..\io_ipc.h"
using namespace std;

// step2. 바인더 정보 관리 클래스는 2개 이상의 객체를 생성할 이유가 없다
// -> 싱글톤 형태로 구현
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
public:
	IPCThreadState() : mProcess(ProcessState::self()) {}	// 싱글톤의 장점: 어디서든 self에 접근 가능 (static이니까)
	// 아래의 함수는 binder_call의 래퍼 함수 입니다.
	int transact(int handle, int code, int* msg, int* reply) {
		int driver = mProcess->getDriver();
		return binder_call(driver, msg, reply, handle, code);
	}
};

int main()
{
	ProcessState* proc(ProcessState::self());
	IPCThreadState* ipc(new IPCThreadState);	// 이것도 싱글톤으로 변경 필요

	int msg, reply;

	int handle = binder_call(proc->getDriver(),
							(int*)"LedService",
							&reply,
							BINDER_SERVICE_MANAGER,
							SVC_MGR_CHECK_SERVICE);
	while (1)
	{	// binder_call : 실제 바인더 정보를 송/수신 한다 (통신)
		//getchar(); binder_call(proc->getDriver(), &msg, &reply, handle, 1);
		//getchar(); binder_call(proc->getDriver(), &msg, &reply, handle, 2);
		getchar(); ipc->transact(handle, 1, &msg, &reply);
		getchar(); ipc->transact(handle, 2, &msg, &reply);
	}

	return 0;
}