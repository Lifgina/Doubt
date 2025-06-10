#pragma once

#include "../../HuEngine.h"

class DoubtJudgeNoView {
public:
	void Load();
	void Initialize();
	void UpdateDoubtJudgeNo(int doubtJudgeNo);


private:
	HE::Sprite sprite_; 
	HE::SpriteFont font_; 
};