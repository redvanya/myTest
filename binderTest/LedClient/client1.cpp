#include <iostream>
#include "..\io_ipc.h"
using namespace std;

// step 1. ���δ� ����̹� ������ ���� �� �����ϱ� ���Ͽ� Ŭ������ �����Ѵ�
class ProcessState {
	int mDriverFD;
public:
	//ProcessState() { mDriverFD = binder_open(128 * 1024); }
	//ProcessState() { mDriverFD = open_driver(); }	// ����
	ProcessState() : mDriverFD(open_driver()) {}	// �ʱ�ȭ
	int getDriver() const { return mDriverFD; }

	// ��� �����ڸ� ���� ������ API
	int open_driver() { return binder_open(128 * 1024); }
};

int main()
{
    // const int fd = binder_open(128*1024);	// device driver open
	//ProcessState proc;	// ��뷮�� �ڷᱸ���� ������ �ƴ� ���� ����� ���� ����
	ProcessState* proc(new ProcessState);	// Android������� ��. �ΰ��� ����. ProcessState* proc = new ProcessState;

    int msg, reply;

    int handle = binder_call(proc->getDriver(),	// fd,
                            (int*)"LedService",
                            &reply,
                            BINDER_SERVICE_MANAGER,
                            SVC_MGR_CHECK_SERVICE);
    while(1)
    {
        //getchar(); binder_call(fd, &msg, &reply, handle, 1);
        //getchar(); binder_call(fd, &msg, &reply, handle, 2);
		getchar(); binder_call(proc->getDriver(), &msg, &reply, handle, 1);
		getchar(); binder_call(proc->getDriver(), &msg, &reply, handle, 2);
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             

    return 0;
}