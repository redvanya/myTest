
#include "../Android.h"

class BBinder : public IBinder
{
protected:
	// 내부 콜백을 사용자가 직접 오버라이딩 하는 것은 좋지 못하므로
	// 외부 콜백 인터페이스로 onTransact를 제공합니다.
	int transact(int code, int* msg, int* reply){
		return onTransact(code, msg, reply);
	}

public:
	virtual int onTransact(int code, int* msg, int* reply) { return 0; }
};

// step 3. 다중 상속을 단일 상속으로 변경하기 위해 아래의 클래스를
// 도입합니다.
template<typename INTERFACE>
class BnInterface : public BBinder, public INTERFACE
{
public:
	IBinder* onAsBinder() { return this; }

};

// 이제 서비스 제작자는 BnInterface를 상속하기로 약속합니다.
// class LedService : public BBinder, public ILedService
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
	// 1. 바인더 드라이버 오픈
	// struct binder_state* bs;
	int fd = binder_open(128 * 1024); // 128KB

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