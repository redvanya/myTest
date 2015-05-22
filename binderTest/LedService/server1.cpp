//#include <iostream>
//#include "..\io_ipc.h"
//using namespace std;
#include "../Android.h"

// step 1. ������ �ڵ嵵 IBinder�� �ڽ����� ������ �Ѵ�
// ���� ������ ������ ���� Ŭ������ BBinder�� �����Ѵ�

class BBinder : public IBinder {
protected:
	int transact(int code, int* msg, int* reply){
		return onTransact(code, msg, reply);
	}
public:
	virtual int onTransact(int code, int* msg, int* reply) { return 0; }	// ���� ������ �ȵȴ� ������ �� ���� ���� ����� �ִ�
};

// ���� �����ڴ� BBinder�� ��� �ް� onTransct�� �������̵� �ϸ� �ȴ�.
class LedService : public BBinder {
public:
	//int myHandler(int code, int* msg, int* reply)
	int onTransact(int code, int* msg, int* reply)
	{
		switch (code)
		{
		case 1: cout << "LED ON" << endl; break;
		case 2: cout << "LED OFF" << endl; break;
		}
		return 0;
	}
};


int main()
{   
    // 1. ���δ� ����̹� ����
    // struct binder_state* bs;
    int fd = binder_open(128*1024); // 128KB: ���Ź���

    // 2. ���� �Ŵ������� ���� �̸� ���
    int reply;
    binder_call(fd,
               (int*)"LedService",
               &reply,
               BINDER_SERVICE_MANAGER,	//0�� ����
               SVC_MGR_ADD_SERVICE);	// RPC �ڵ�

    // 3. Ŭ���̾�Ʈ�� ��û ���
    binder_loop(fd, myHandler);
    return 0;
}