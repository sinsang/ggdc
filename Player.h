#pragma once
#include <Zero.h>
#include <fstream>
#include <string>

using namespace std;

class Player : public ZeroIScene {
public:
	Player();
	~Player();

	void Update(float eTime);
	void Render();

	ZeroAnimation *PlayerAnimation;

	int PlayerPosX, PlayerPosY;
	int JumpToCorrectPosY, Sin;
	int BackgroundWidth, BackgroundHeight;

	int FrameCount;
};
