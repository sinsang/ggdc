#pragma once
#include <Zero.h>
#include "Main.h"

class Briefing : public ZeroIScene {
public:
	Briefing();
	~Briefing();

	void Update(float eTime);
	void Render();

	// 파트너 선택하는 배열들
	ZeroSprite *Partner[3];
	ZeroSprite *Select;
	bool IsPartnerSelected[3];

	ZeroSprite *StartButton;

	ZeroFont *ProcessInformation;
	ZeroRegulator *ProcessInformationRegulator;
};
