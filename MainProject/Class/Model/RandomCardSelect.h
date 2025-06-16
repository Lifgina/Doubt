#pragma once

#include "../../HuEngine.h"
#include "CardData.h"

class RandomCardSelect {
public:
	void CardSelect(int hands,int judgeNo,CardData cards[]);
	int GetSelectedCardIndex(int index) const {
		return selectedCardIndex_[index];
	}

private:
	int selectedCardIndex_[4]; // �I�����ꂽ�J�[�h�̃C���f�b�N�X��������
	float correctDiscardRate_ = 0.7; // �������J�[�h���J�[�h���o���m��
	float discard1Rate_ = 0.4; // 1���̂Ă�m��
	float discard2Rate_ = 0.3; // 2���̂Ă�m��
	float discard3Rate_ = 0.2; // 3���̂Ă�m��
	//4���̂Ă�m����1 - (discard1Rate_ + discard2Rate_ + discard3Rate_)

};