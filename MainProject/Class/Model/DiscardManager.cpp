//
// DiscardManager.cpp
//

#include "DiscardManager.h"

using namespace HE;

void DiscardManager::SetDiscard(CardData nowdiscard) {
		currentDiscard_[currentDiscardCount_] = nowdiscard;
		++currentDiscardCount_;
		discard_[discardCount_] = nowdiscard;
		++discardCount_;
}
void DiscardManager::ClearDiscard() {
	// 捨て札をクリア
	ClearCurrentDiscard();
	discardCount_ = 0;
	for (int i = 0; i < 52; ++i) {
		discard_[i] = CardData(); // 初期化
	}
}

void DiscardManager::ClearCurrentDiscard() {
	// 直前の捨て札の枚数
	currentDiscardCount_ = 0;
	for (int i = 0; i < 4; ++i) {
		currentDiscard_[i] = CardData(); // 初期化
	}
}