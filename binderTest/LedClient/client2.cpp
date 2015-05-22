#include <iostream>
#include "..\io_ipc.h"
using namespace std;

// step2. 바인더 정보 관리 클래스는 2개 이상의 객체를 생성할 이유가 없다
// -> 싱글톤 형태로 구현
class ProcessState {
	int mDriverFD;

	// 1. 생성자는 private 영역에 정의
	ProcessState() : mDriverFD(open_driver()) {}
	static ProcessState* pInstance;

	// 3. 복사와 대입을 금지하기 위해 복사 생성자와 대입 연산자 함수를 private 영역에 선언 (구현은 안해도됨)
	ProcessState(const ProcessState&);
	void operator = (const ProcessState&);

public:
	// 2. 유일한 객체를 반환하기 위한 정적 인터페이스를 도입
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
	//ProcessState* proc(new ProcessState);	// 여러개 메모리 할당 되면 낭비 -> 싱글톤 형태로 만들자
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