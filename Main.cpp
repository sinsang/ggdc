#include "Main.h"

Main::Main(int _PartnerIndex1, int _PartnerIndex2) 
: PartnerIndex1(_PartnerIndex1), PartnerIndex2(_PartnerIndex2) {
	ProcessInformation = new ZeroFont(20, "");
	ProcessInformationRegulator = new ZeroRegulator(2.0f);
	Heroine = new Player();
	Background = new ZeroSprite("Texture/UI/Background_%d.png", 1);
	Partner1 = new Partner(_PartnerIndex1);
	Partner2 = new Partner(_PartnerIndex2);

	ProcessInformation->SetColor(0xffaaaaaa);
	ProcessInformation->SetCamera(false);

	PushScene(ProcessInformation);
	PushScene(Heroine);
	PushScene(Background);
	PushScene(Partner1);
	PushScene(Partner2);

	ZeroCameraMgr->SetCameraOn();
	ZeroCameraMgr->SetTarget(Heroine);
	ZeroCameraMgr->SetScreen(Background->Width(), Background->Height());
}

Main::~Main() {
	PopScene(ProcessInformation);
	PopScene(Heroine);
	PopScene(Background);
}

void Main::Update(float eTime) {
	if (ProcessInformationRegulator->IsReady()) {
		ProcessInformation->SetString("FPS: %.2f, Memory Usage: %.2fMB, CPU Usage: %.2f%%",
			ZeroApp->GetFPS(), ZeroApp->GetMemoryUsage(), ZeroApp->GetCpuUsage());
	}

	if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN && !Heroine->Sin) {
		// 점프가 진행 중이지 않으면 점프를 시작시킨다.
		Heroine->Sin = 5;
	}

	if (ZeroInputMgr->GetKey(VK_ESCAPE) == INPUTMGR_KEYON) {
		exit(EXIT_SUCCESS);
	}

	Heroine->BackgroundWidth = Background->Width();
	Heroine->BackgroundHeight = Background->Height();

	Partner1->SetPos
		(Heroine->PlayerPosX - 200 >= 0 ? Heroine->PlayerPosX - 200 : 0, 
		 Heroine->PlayerPosY - 200 >= 0 ? Heroine->PlayerPosY - 200 : 0);
	Partner2->SetPos
		(Heroine->PlayerPosX - 200 >= 0 ? Heroine->PlayerPosX - 200 : 0, 
		Heroine->PlayerPosY + 200 <= Background->Height() - Partner2->Height() ? 
		Heroine->PlayerPosY + 200 : Background->Height() - Partner2->Height());

	ZeroIScene::Update(eTime);
}

void Main::Render() {
	ZeroIScene::Render();
	Background->Render();
	Heroine->Render();
	Partner1->Render();
	Partner2->Render();

	ProcessInformation->Render();
}
