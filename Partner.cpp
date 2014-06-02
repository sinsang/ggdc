#include "Partner.h"

Partner::Partner(int _PartnerIndex) : PartnerIndex(_PartnerIndex) {
	// 프레임 수 불러오기
	string path = "Texture/Partner/"; path += _PartnerIndex + '0'; path += "/settings.ini";
	std::ifstream fi(path);
	fi >> FrameCount;
	fi.close();

	Charactor = new ZeroAnimation(FrameCount);

	for (int i = 0; i < FrameCount; i++) {
		Charactor->PushSprite("Texture/Partner/%d/Partner_%d.png", _PartnerIndex, i + 1);
	}

	PushScene(Charactor);

	this->SetWidth(Charactor->Width());
	this->SetHeight(Charactor->Height());
}

Partner::~Partner() {
	PopScene(Charactor);
}

void Partner::Update(float eTime) {
	ZeroIScene::Update(eTime);
}

void Partner::Render() {
	ZeroIScene::Render();
	Charactor->Render();
}
