#include "Player.h"

Player::Player() {
	// 프레임 수 불러오기
	string path = "Texture/Player/settings.ini";
	std::ifstream fi(path);
	fi >> FrameCount;
	fi.close();

	PlayerAnimation = new ZeroAnimation((float) FrameCount);
	for (int i = 0; i < FrameCount; i++)
		PlayerAnimation->PushSprite("Texture/Player/Player_%d.png", i + 1);

	this->SetWidth(PlayerAnimation->Width());
	this->SetHeight(PlayerAnimation->Height());

	PushScene(PlayerAnimation);

	// 초기 위치 설정
	PlayerPosX = 300;
	PlayerPosY = 400;

	Sin = 0;
	JumpToCorrectPosY = 0;
}

Player::~Player() {
	PopScene(PlayerAnimation);
}

void Player::Update(float eTime) {
	// Sin 값이 Main 함수에서 바뀌면 점프 시작
	if (Sin) {
		Sin += 5;
		JumpToCorrectPosY = ZeroMathMgr->Sin(Sin) * 200;
		if (Sin >= 180) {
			Sin = 0;
			JumpToCorrectPosY = 0;
		}
	}

	// 외부로 나가지 못하도록 하기
	if (ZeroInputMgr->GetKey('A') == INPUTMGR_KEYON) {
		if (PlayerPosX + (-800 * eTime) >= 0)
			PlayerPosX += -800 * eTime;
		else
			PlayerPosX = 0;
	}
	if (ZeroInputMgr->GetKey('D') == INPUTMGR_KEYON) {
		if (PlayerPosX + (800 * eTime) + this->Width() <= BackgroundWidth)
			PlayerPosX += 800 * eTime;
		else
			PlayerPosX = BackgroundWidth - this->Width();
	}
	if (ZeroInputMgr->GetKey('W') == INPUTMGR_KEYON) {
		if (PlayerPosY + (-400 * eTime) >= 0)
			PlayerPosY += -400 * eTime;
		else
			PlayerPosY = 0;
	}
	if (ZeroInputMgr->GetKey('S') == INPUTMGR_KEYON) {
		if (PlayerPosY + (400 * eTime) + this->Height() <= BackgroundHeight)
			PlayerPosY += 400 * eTime;
		else
			PlayerPosY = BackgroundHeight - this->Height();
	}

	// pPlayer 객체가 아닌 Player 객체가 이동해야 함
	this->SetPos(PlayerPosX, PlayerPosY - JumpToCorrectPosY);

	ZeroIScene::Update(eTime);
}

void Player::Render() {
	ZeroIScene::Render();
	PlayerAnimation->Render();
}
