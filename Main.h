#pragma once
#include <Zero.h>
#include "Player.h"
#include "Partner.h"

class Main : public ZeroIScene {
public:
	Main(int _PartnerIndex1, int _PartnerIndex2);
	~Main();

	void Update(float eTime);
	void Render();

	ZeroFont *ProcessInformation;
	ZeroRegulator *ProcessInformationRegulator;

	Player *Heroine; // 플레이어가 실제 조종하는 객체
	ZeroSprite *Background;
	Partner *Partner1, *Partner2;
	int PartnerIndex1, PartnerIndex2; // 파트너의 인덱스 값
};
