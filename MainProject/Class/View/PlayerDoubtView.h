#pragma once

#include "../../HuEngine.h"

class PlayerDoubtView {
public:
	void Load();
	void ShowDoubtMenu();
	void HideDoubtMenu();


private:
	HE::SpriteFont doubtText_[3]; // �_�E�g�̃e�L�X�g��\������t�H���g
};