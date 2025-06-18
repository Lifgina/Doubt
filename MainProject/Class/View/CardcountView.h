#pragma once

#include "../../HuEngine.h"

class CardcountView {
public:
	void Load();
	void Initialize(HE::Math::Vector2 position);
	void SetPlayerID(int playerID);
	void UpdateCardcount(int playerCardcount);


private:
	HE::Sprite cardBackSprite_; // �J�[�h�̗��ʂ�\������X�v���C�g
	HE::SpriteFont cardCountsFont_;
	HE::SpriteFont playerIDFont_; // �v���C���[ID��\������t�H���g
};