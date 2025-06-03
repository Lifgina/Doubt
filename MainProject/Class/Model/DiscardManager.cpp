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
	// �̂ĎD���N���A
	ClearCurrentDiscard();
	discardCount_ = 0;
	for (int i = 0; i < 52; ++i) {
		discard_[i] = CardData(); // ������
	}
}

void DiscardManager::ClearCurrentDiscard() {
	// ���O�̎̂ĎD�̖���
	currentDiscardCount_ = 0;
	for (int i = 0; i < 4; ++i) {
		currentDiscard_[i] = CardData(); // ������
	}
}