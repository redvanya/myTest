#include "../Android.h"

class BBinder : public IBinder {
protected:
	int transact(int code, int* msg, int* reply) {
		return onTransact(code, msg, reply);
	}
public:
	virtual int onTransact(int code, int* msg, int* reply) { return 0; }
};

// step 3. 다중 상속을 단일 상속으로 변경하기 위해 아래의 클래스를 도입한다.
template<typename INTERFACE>
class BnInterface : public BBinder, public INTERFACE {
public:
	IBinder* onAsBinder() { return this; }
};

// 이제 서비스 제작자는 BnInterface를 상속하기로 약속합니다.
//class LedService : public BBinder, public ILedService {	// 다중 상속 발생
class LedService : public BnInterface<ILedService> {
public:
	void ledOn() { cout << "LED ON" << endl; }
	void ledOff() { cout << "LED OFF" << endl; }

	int onTransact(int code, int* msg, int* reply) {
		switch (code) {
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
	int fd = binder_open(128 * 1024); // 128KB: 수신버퍼

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