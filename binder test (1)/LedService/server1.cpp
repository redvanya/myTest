

//#include <iostream>
//#include "..\io_ipc.h"
//using namespace std;

// 위의 코드를 주석으로 막고 아래의 헤더를 포함시키세요 :D
#include "../Android.h"

// step 1. 서비스의 코드도 IBinder의 자식으로 만들어야 합니다.
// 서비스 구현을 도와줄 헬퍼 클래스로 BBinder를 제공합니다.
class BBinder : public IBinder
{
protected:
	int transact(int code, int* msg, int* reply)
	{
		return onTransact(code, msg, reply);
	}

public:
	virtual int onTransact(int code, int* msg, int* reply) { return 0; }
};

// 서비스 제작자는 BBinder를 상속 받고 onTransact를 오버라이딩 하면 됩니다.
class LedService : public BBinder
{
public:
	// int myHandler(int code, int* msg, int* reply)
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
    // 1. 바인더 드라이버 오픈
    // struct binder_state* bs;
    int fd = binder_open(128*1024); // 128KB

    // 2. 서비스 매니저에게 서버 이름 등록
    int reply;
    binder_call(fd,
               (int*)"LedService",
               &reply,
               BINDER_SERVICE_MANAGER,
               SVC_MGR_ADD_SERVICE);

    // 3. 클라이언트의 요청 대기
    binder_loop(fd, myHandler);
    return 0;
}