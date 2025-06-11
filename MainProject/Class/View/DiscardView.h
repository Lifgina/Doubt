#pragma once

#include "../../HuEngine.h"

class DiscardView {
public:
	void Load();
	void Initialize(int playerCount,int myPlayerID);
	void Discard(int playerID,int currentDiscardCount);
	void ResetDiscard();


private:
	int playerCount_;
	int myPlayerID_; // �����̃v���C���[ID
	int discardCount_;
	HE::Sprite cardSprite_[52]; // �̂ĎD�̃J�[�h�X�v���C�g
};