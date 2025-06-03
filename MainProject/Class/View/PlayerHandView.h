#pragma once

#include "../../HuEngine.h"

class PlayerHandView {
public:
	void Load();
	void Initialize();
	void Update();


private:
	HE::Sprite playerHandSprites_[52]; // プレイヤーの手札を表示するスプライト
};