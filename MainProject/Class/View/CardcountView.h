#pragma once

#include "../../HuEngine.h"

class CardcountView {
public:
	void Load();
	void Initialize(HE::Math::Vector2 position);
	void UpdateCardcount(int playerCardcount);


private:
	HE::Sprite cardBackSprite_; // カードの裏面を表示するスプライト
	HE::SpriteFont cardCountsFont_;
};