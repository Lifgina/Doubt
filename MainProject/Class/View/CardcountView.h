#pragma once

#include "../../HuEngine.h"

class CardcountView {
public:
	void Load();
	void Initialize(HE::Math::Vector2 position);
	void UpdateCardcount(int playerCardcount);


private:
	HE::Sprite cardBackSprite_; // �J�[�h�̗��ʂ�\������X�v���C�g
	HE::SpriteFont cardCountsFont_;
};