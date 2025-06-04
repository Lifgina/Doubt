#pragma once

#include "../../HuEngine.h"

class MarkerView {
public:
	void Load();
	void UpdateMarker(HE::Math::Vector2 cardpos);
	void MarkerDelete();

private:
	HE::Sprite markerSprite_; // マーカーのスプライト
};