#pragma once

#include "../../HuEngine.h"

class TurnPlayerView {
public:
	void Load();
	void Initialize();
	void UpdateTurnPlayerView(int turnPlayerID);


private:
	HE::SpriteFont turnPlayerFont_; // �^�[���̃v���C���[��\������t�H���g
};