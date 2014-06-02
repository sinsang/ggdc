#include "Briefing.h"

Briefing::Briefing() {
	Select = new ZeroSprite("Texture/Briefing/Partner_Selected.png");
	StartButton = new ZeroSprite("Texture/Briefing/Start.png");

	ProcessInformation = new ZeroFont(20, "");
	ProcessInformationRegulator = new ZeroRegulator(2.0f);

	ProcessInformation->SetColor(0xffaaaaaa);

	StartButton->SetPos(500, 500);

	PushScene(Select);
	PushScene(StartButton);
	PushScene(ProcessInformation);

	for (int i = 0; i < 3; i++) {
		Partner[i] = new ZeroSprite("Texture/Briefing/Partner_%d.png", i + 1);
		Partner[i]->SetPos(i * 310, 20);
		PushScene(Partner[i]);

		IsPartnerSelected[i] = false;
	}
}

Briefing::~Briefing() {
	PopScene(Select);
	PopScene(StartButton);
	PopScene(ProcessInformation);

	for (int i = 0; i < 3; i++) {
		PopScene(Partner[i]);
	}
}

void Briefing::Update(float eTime) {
	ZeroIScene::Update(eTime);

	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN) {
		for (int i = 0; i < 3; i++) {
			if (Partner[i]->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
				if (IsPartnerSelected[i] || IsPartnerSelected[0] + IsPartnerSelected[1] + IsPartnerSelected[2] < 2)
					IsPartnerSelected[i] = !IsPartnerSelected[i];
			}
		}
		if (IsPartnerSelected[0] + IsPartnerSelected[1] + IsPartnerSelected[2] == 2 &&
			StartButton->IsOverlapped(ZeroInputMgr->GetClientPoint())) {

			int PartnerIdx1, PartnerIdx2;
			if (IsPartnerSelected[0] && IsPartnerSelected[1]) {
				PartnerIdx1 = 0;
				PartnerIdx2 = 1;
			}
			else if (IsPartnerSelected[0] && IsPartnerSelected[2]) {
				PartnerIdx1 = 0;
				PartnerIdx2 = 2;
			}
			else {
				PartnerIdx1 = 1;
				PartnerIdx2 = 2;
			}

			ZeroSceneMgr->ChangeScene(new Main(PartnerIdx1, PartnerIdx2));
			return;
		}
	}

	if (ProcessInformationRegulator->IsReady()) {
		ProcessInformation->SetString("FPS: %.2f, Memory Usage: %.2fMB, CPU Usage: %.2f%%",
			ZeroApp->GetFPS(), ZeroApp->GetMemoryUsage(), ZeroApp->GetCpuUsage());
	}
}

void Briefing::Render() {
	ZeroIScene::Render();

	for (int i = 0; i < 3; i++) {
		Partner[i]->Render();
		if (IsPartnerSelected[i]) {
			Select->SetPos(Partner[i]->Pos());
			Select->Render();
		}
	}

	if (IsPartnerSelected[0] + IsPartnerSelected[1] + IsPartnerSelected[2] == 2) {
		StartButton->Render();
	}

	ProcessInformation->Render();
}
