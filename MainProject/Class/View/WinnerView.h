#pragma once

#include "../../HuEngine.h"

class WinnerView {
public:
	void Load();
	void ShowWinner(int winnerPlayerID); // ���҂�\������֐�


private:
	HE::SpriteFont winnerFont_[2]; // ���҂�\������t�H���g
	HE::SpriteFont toTitleFont_; // �^�C�g���֖߂�t�H���g
};