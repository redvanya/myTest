
#include <iostream>
#include "..\io_ipc.h"
using namespace std;

// step 1. 바인더 드라이버 정보를 저장 및 관리하기 위하여 클래스를 도입합니다.
class ProcessState
{
	int mDriverFD;
public:
	// ProcessState() { mDriverFD = binder_open(128 * 1024); }
	// ProcessState() { mDriverFD = open_driver(); }
	ProcessState() : mDriverFD(open_driver()) {}

	int getDriver() { return mDriverFD; }

	// 고급 개발자를 위한 저수준 API
	int open_driver() { return binder_open(128 * 1024); }
};

int main()
{
    // const int fd = binder_open(128*1024);
	// ProcessState* proc = new ProcessState;	// ProcessState proc;
	ProcessState* proc(new ProcessState);

    int msg, reply;
    int handle = binder_call(proc->getDriver(), // fd,
                            (int*)"LedService",
                            &reply,
                            BINDER_SERVICE_MANAGER,
                            SVC_MGR_CHECK_SERVICE);
    while(1)
    {
        // getchar(); binder_call(fd, &msg, &reply, handle, 1);
		getchar(); binder_call(proc->getDriver(), &msg, &reply, handle, 1);
		// getchar(); binder_call(fd, &msg, &reply, handle, 2);
		getchar(); binder_call(proc->getDriver(), &msg, &reply, handle, 2);
    }
    return 0;
}