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

	int PartnerIndex; // ��Ʈ���� �ε���. ������ 0���� 2
	int FrameCount; // ���� ��������� �޾Ƶ��̴� ������ ��
};
