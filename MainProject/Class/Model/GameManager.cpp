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
	int discardIndex_[4] = { -1, -1, -1, -1 };
	if (turnPlayerID_ == 0) {
		if (!isInputed_) {
			return;
		}
		for (int i = 0; i < 4; ++i) {
			discardIndex_[i] = playerDiscardIndex_[i];
		}
	}
	else {
		int hands = player_[turnPlayerID_].GetPlayerHands();
		CardData handcards[52];
		for (int i = 0; i < hands; ++i) {
			handcards[i] = player_[turnPlayerID_].GetCard(i);
		}
		randomCardSelect_.CardSelect(hands, doubtJudgeNo_, handcards);
		for (int i = 0; i < 4; ++i) {
			discardIndex_[i] = randomCardSelect_.GetSelectedCardIndex(i);
		}
	}
	// �C���f�b�N�X�̑傫�����ɍ폜
	std::vector<int> sortedIndices;
	for (int i = 0; i < 4; ++i) {
		if (discardIndex_[i] != -1) {
			sortedIndices.push_back(discardIndex_[i]);
		}
	}
	std::sort(sortedIndices.rbegin(), sortedIndices.rend());
	for (int idx : sortedIndices) {
		discardManager_.SetDiscard(player_[turnPlayerID_].GetCard(idx));
		player_[turnPlayerID_].DisCard(idx);
	}
	isDiscardTurn_ = false;
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
	bool isDoDoubt = false; // �_�E�g�����邩�ǂ����̃t���O
	if (turnPlayerID_ == 0) {
		
	}
	else {
		
	}

	if (isDoDoubt) {
		DoubtCheck();
	}

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
