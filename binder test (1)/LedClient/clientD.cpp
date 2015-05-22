
#include "../Android.h"

// ILedService 클래스부터 시작하여 그 위의 모든 코드를 잘라내기 하여
// 현재 프로젝트 폴더의 상위 폴더에 Android.h 파일을 만들고
// 안에 붙여넣으세요 :D

class BpLedService : public BpInterface<ILedService>	// CRTP
{
	int msg, reply;
public:
	BpLedService(IBinder* p) : BpInterface(p) {}
	void ledOn() { remote()->transact(1, &msg, &reply); }
	void ledOff() { remote()->transact(2, &msg, &reply); }
};
// ILedService* ILedService::asInterface(IBinder* p) { return new BpLedService(p); }
IMPLEMENT_META_INTERFACE(LedService)

int main()
{
	ProcessState* proc(ProcessState::self());
	IBinder* binder = getService("LedService");
	ILedService* ledService = interface_cast<ILedService>(binder);

	while (1)
	{
		getchar(); ledService->ledOn();
		getchar(); ledService->ledOff();
	}
	return 0;
}