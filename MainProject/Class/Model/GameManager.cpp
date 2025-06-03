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
	int discardIndex_[4] = { -1, -1, -1, -1 }; // �̂ĎD�̃C���f�b�N�X��������
	//
	if (turnPlayerID_ == 0) {
		//isInputed_�������Ă��Ȃ��ꍇ�͂����ŏ������~�߂Ă���
		if (!isInputed_) {
			return; // ���͂��܂�����Ă��Ȃ��ꍇ�͏����𒆒f
		}
		for (int i = 0; i < 4; ++i) {
			discardIndex_[i] = playerDiscardIndex_[i]; // �v���C���[���I�������J�[�h�̃C���f�b�N�X���擾
		}
	}
	else {
		int hands = player_[turnPlayerID_].GetPlayerHands();
		CardData handcards[52]; // ��D�̃J�[�h���i�[����z��
		for (int i = 0; i < hands; ++i) {
			handcards[i] = player_[turnPlayerID_].GetCard(i); // ��D�̃J�[�h���擾
		}
		randomCardSelect_.CardSelect(hands,doubtJudgeNo_,handcards); // �����_���ɃJ�[�h��I��
		for (int i = 0; i < 4; ++i) {	
			discardIndex_[i] = randomCardSelect_.GetSelectedCardIndex(i); // �I�����ꂽ�J�[�h�̃C���f�b�N�X���擾
		}
	}
	// �I�����ꂽ�J�[�h���̂ĎD�ɒǉ�
	for (int i = 0; i < 4; ++i) {
		if (discardIndex_[i] != -1) {
			discardManager_.SetDiscard(player_[turnPlayerID_].GetCard(discardIndex_[i]));
			player_[turnPlayerID_].DisCard(discardIndex_[i]);
		}
	}
	isDiscardTurn_ = false; // �̂ĎD�̃^�[�����I��
}

void GameManager::SetPlayerDiscard(int cardIndex[])
{
	for (int i = 0; i < playerCount_; ++i) {
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
