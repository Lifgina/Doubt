#pragma once

#include "../../HuEngine.h"
#include "CardData.h"

class DiscardManager {
public:
	void SetDiscard(CardData nowdiscard);
	CardData GetCurrentDisCards(int index) const { return currentDiscard_[index]; } // ���O�̎̂ĎD���擾 
	CardData GetDiscard(int index) const { return discard_[index]; } // �̂ĎD���擾
	void ClearDiscard();  // �̂ĎD���N���A
	void ClearCurrentDiscard();// ���݂̎̂ĎD�̖��������Z�b�g

private:
	int currentDiscardCount_ = 0; // ���݂̎̂ĎD�̖���
	int discardCount_ = 0; // ���݂̎̂ĎD�̖���	
	CardData currentDiscard_[4]; // ���O�̎̂ĎD
	CardData discard_[52];//�̂ĎD
};