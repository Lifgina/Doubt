#pragma once

#include "../../HuEngine.h"
#include "../Model/PlayerData.h"

class PlayerHandView {
public:
	void Load();
	void UpdatePlayerHands(PlayerData playerdata_);


private:
	HE::Sprite playerHandSprites_[52]; // �v���C���[�̎�D��\������X�v���C�g
};