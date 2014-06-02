#pragma once
#include <Zero.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class Partner : public ZeroIScene {
public:
	Partner(int _PartnerIndex);
	~Partner();

	void Update(float eTime);
	void Render();

	ZeroAnimation *Charactor;

	int PartnerIndex; // 파트너의 인덱스. 범위는 0부터 2
	int FrameCount; // 파일 입출력으로 받아들이는 프레임 수
};
