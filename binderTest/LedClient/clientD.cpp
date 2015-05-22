#include "../Android.h"

// ILedService Ŭ�������� �����Ͽ� �� ���� ��� �ڵ带 �߶󳻱� �Ͽ�
// ���� ������Ʈ ������ ���� ������ Android.h ������ �����

class BpLedService : public BpInterface<ILedService> {	// CRTP
	int msg, reply;
public:
	BpLedService(IBinder* p) : BpInterface<ILedService>(p) {}
	void ledOn() { remote()->transact(1, &msg, &reply); }
	void ledOff() { remote()->transact(2, &msg, &reply); }
};

//ILedService* ILedService::asInterface(IBinder* p){
//	return new BpLedService(p);
//}
//IMPLEMENT_META_INTERFACE(ILedService)	// Bp##INTERFACE -> BpILedService�� �Ǿ ERROR (BpLedService�� �Ǿ����)
IMPLEMENT_META_INTERFACE(LedService)	// �׷��� I�� ���� �ѱ�� ��� ��ũ�ο��� I##INTERFACE���� ���� (���)

int main()
{
	ProcessState* proc = ProcessState::self();
	IBinder* binder = getService("LedService");
	ILedService* ledService = interface_cast<ILedService>(binder);

	while (1)
	{
		getchar(); ledService->ledOn();
		getchar(); ledService->ledOff();
	}
	return 0;
}