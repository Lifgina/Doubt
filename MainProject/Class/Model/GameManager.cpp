//
// GameManager.cpp
//

#include "GameManager.h"

using namespace HE;

void GameManager::Load()
{
	
}

void GameManager::Initialize()
{
	turnPlayerID_ = myPlayerID_;
	cardDistributer_.DistributeCards(player_, playerCount_);
	doubtJudgeNo_ =1;
	isDiscardTurn_ = true; // ������Ԃł͎̂ĎD�̃^�[��
	isInputed_ = false; // ���͂��܂�����Ă��Ȃ����
	
}

void GameManager::Update()
{
	if (isDiscardTurn_) {
		DiscardTurn();
	}
	else {
		DoubtTurn();
	}
}
void GameManager::DiscardTurn()
{
	cardDiscarder_.Discard(
		player_,
		playerCount_,
		turnPlayerID_,
		myPlayerID_,
		doubtJudgeNo_,
		playerDiscardIndex_,
		isInputed_,
		discardManager_,
		randomCardSelect_,
		isInputed_,
		isDiscardTurn_
	);
}

void GameManager::SetPlayerDiscard(int cardIndex[4])
{
	for (int i = 0; i < 4; ++i) {
		playerDiscardIndex_[i] = cardIndex[i];
	}
	isInputed_ = true; // ���͂��ꂽ�t���O�𗧂Ă�
}

void GameManager::DoubtTurn()
{
	//�_�E�g�^�[���̏���
	for(int i=0;i<playerCount_;i++){
		turnPlayerID_ = (turnPlayerID_ + 1) % playerCount_; // ���̃v���C���[�Ƀ^�[�����ڂ�
		if (turnPlayerID_ == myPlayerID_) {
			if (!isInputed_) {
				return;
			}
		}
		else {

		}
	}

}

void GameManager::SetPlayerDoDoubt(bool isDoubt)
{
	isDoubt_ = isDoubt; // �_�E�g�̃t���O��ݒ�
	isInputed_ = true; // ���͂��ꂽ�t���O�𗧂Ă�
}

void GameManager::DoubtCheck()
{
	for (int i = 0; i < 4; ++i) {
		CardData card = discardManager_.GetCurrentDisCards(i);
		// rank��0�̏ꍇ�͖��g�p�X���b�g�Ƃ݂Ȃ��i���������j
		if (card.GetRank() == 0) continue;

		if (card.GetRank() != doubtJudgeNo_) {
			
			break;
		}

	}

}

void GameManager::Penalty()
{
   
}
