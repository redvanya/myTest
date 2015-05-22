
#include "../Android.h"


//------------------------------------------------------------------------
// 아래의 코드는 서비스 제작자가 구현하는 코드입니다.

// 안드로이드가 제공하는 코드를 모두 Android.h 파일에 붙여넣으세요

class LedService : public BnInterface<ILedService>
{
public:
	void ledOn() { cout << "LED ON" << endl; }
	void ledOff() { cout << "LED OFF" << endl; }

	int onTransact(int code, int* msg, int* reply)
	{
		switch (code)
		{
		case 1: ledOn(); break;
		case 2: ledOff(); break;
		}
		return 0;
	}
};



int main()
{
	ProcessState* proc(ProcessState::self());

	// 2. 서비스 매니저에게 서버 이름 등록
	//int reply;
	//binder_call(fd,
	//	(int*)"LedService",
	//	&reply,
	//	BINDER_SERVICE_MANAGER,
	//	SVC_MGR_ADD_SERVICE);
	
	// defaultServiceManager()->addService(String16("LedService"), new LedService);
	addService("LedService", new LedService);


	// 3. 클라이언트의 요청 대기
	// binder_loop(fd, myHandler);
	IPCThreadState::self()->joinThreadPool();
	return 0;
}