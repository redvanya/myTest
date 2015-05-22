//#include <iostream>
//#include "..\io_ipc.h"
//using namespace std;
#include "../Android.h"

// step 1. 서비스의 코드도 IBinder의 자식으로 만들어야 한다
// 서비스 구현을 도와줄 헬퍼 클래스로 BBinder를 제공한다

class BBinder : public IBinder {
protected:
	int transact(int code, int* msg, int* reply){
		return onTransact(code, msg, reply);
	}
public:
	virtual int onTransact(int code, int* msg, int* reply) { return 0; }	// 순수 가상은 안된다 제작자 중 구현 안할 사람도 있다
};

// 서비스 제작자는 BBinder를 상속 받고 onTransct를 오버라이딩 하면 된다.
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
    // 1. 바인더 드라이버 오픈
    // struct binder_state* bs;
    int fd = binder_open(128*1024); // 128KB: 수신버퍼

    // 2. 서비스 매니저에게 서버 이름 등록
    int reply;
    binder_call(fd,
               (int*)"LedService",
               &reply,
               BINDER_SERVICE_MANAGER,	//0번 서비스
               SVC_MGR_ADD_SERVICE);	// RPC 코드

    // 3. 클라이언트의 요청 대기
    binder_loop(fd, myHandler);
    return 0;
}