//
// GameManager.cpp
//

#include "GameManager.h"
#include <random>

using namespace HE;

void GameManager::Load()
{
	
}

void GameManager::Initialize()
{
	turnPlayerID_ = myPlayerID_;
	cardDistributer_.DistributeCards(player_, playerCount_);
	doubtJudgeNo_ =1;
	winnerPlayerID_ = -1; // ������Ԃł͏��҂͖���`
	isDiscardTurn_ = true; // ������Ԃł͎̂ĎD�̃^�[��
	isInputed_ = false; // ���͂��܂�����Ă��Ȃ����
	
}

void GameManager::Update()
{
	if (winnerPlayerID_ != -1) {
		return; // ���҂����܂��Ă���ꍇ�͉������Ȃ�
	}
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
	doubtplayerID_ = turnPlayerID_ ; // �_�E�g���s���v���C���[��ID
	//�_�E�g�^�[���̏���
	for(int i=0;i<playerCount_;i++){
		doubtplayerID_ = (doubtplayerID_ + 1) % playerCount_; // ���̃v���C���[�Ƀ^�[�����ڂ�
		if (doubtplayerID_ == myPlayerID_) {
			if (!isInputed_) {
				return;
			}
		}
		else {
			//�v���C���[�̎�D���擾
			int hands = player_[doubtplayerID_].GetPlayerHands();
			CardData handcards[52];
			for (int j = 0; j < hands; ++j) {
				handcards[j] = player_[doubtplayerID_].GetCard(j);
			}
			//doubtJudgeNo�̃J�[�h���������邩���J�E���g
			int count = 0;
			for (int j = 0; j < hands; ++j) {
				if (handcards[j].GetRank() == doubtJudgeNo_) {
					count++;
				}
			}
			//count�̒l�ɉ������m���ŁA�_�E�g�����邩�ǂ��������߂�
			float doubtProbability = 0.0f;
			if (count == 0) {
				doubtProbability = 0.05f; // 0���Ȃ獂�m���Ń_�E�g
			}
			else if (count == 1) {
				doubtProbability = 0.1f;
			}
			else if (count == 2) {
				doubtProbability = 0.3f;
			}
			else if(count == 3){
				doubtProbability = 0.8f; 
			}
			else {
				doubtProbability = 1.0f; // 4���Ȃ�K���_�E�g
			}

			// ��������
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_real_distribution<float> dist(0.0f, 1.0f);

			if (dist(gen) < doubtProbability) {
				isDoubt_ = true; // �_�E�g����t���O�𗧂Ă�
			}
			else {
				isDoubt_ = false; // �_�E�g���Ȃ��t���O�𗧂Ă�
			}

		}
		// �_�E�g�`�F�b�N���s���A���������瑦����DoubtTurn���I��
		if (isDoubt_)
		{
			if (DoubtCheck(doubtplayerID_, turnPlayerID_)) {
				Penalty(turnPlayerID_); // �_�E�g�����������ꍇ�A��D���̂Ă��v���C���[�Ƀy�i���e�B��^����
				isDoubt_ = false; // �_�E�g�t���O�����Z�b�g
				isInputed_ = false; // ���̓t���O�����Z�b�g
				
			}
			else {
				Penalty(doubtplayerID_); // �_�E�g�����s�����ꍇ�A�_�E�g�����v���C���[�Ƀy�i���e�B��^����
			}
		}
		
	}
	// �_�E�g�^�[�����I���������A�^�[���v���C���[�̎�D��0���ɂȂ����ꍇ�A���҂�ݒ�
	if (player_[turnPlayerID_].GetPlayerHands() == 0) {
		winnerPlayerID_ = turnPlayerID_; // ���҂�ݒ�
		return; // ���҂����܂����̂ŏI��
	}
	turnPlayerID_ = (turnPlayerID_ + 1) % playerCount_; // ���̃v���C���[�Ƀ^�[�����ڂ�
	doubtJudgeNo_ = (doubtJudgeNo_ % 13) + 1; // �_�E�g����̃J�[�h�ԍ������̔ԍ��ɍX�V�i1-13�͈̔͂ŏz�j
	isDiscardTurn_ = true; // �_�E�g�^�[�����I��������A���͎̂ĎD�̃^�[���ɂ���

}

void GameManager::SetPlayerDoDoubt(bool isDoubt)
{
	isDoubt_ = isDoubt; // �_�E�g�̃t���O��ݒ�
	isInputed_ = true; // ���͂��ꂽ�t���O�𗧂Ă�
}

bool GameManager::DoubtCheck(int doubtPlayerID,int discardPlayerID)
{
	for (int i = 0; i < 4; ++i) {
		CardData card = discardManager_.GetCurrentDisCards(i);
		// rank��0�̏ꍇ�͖��g�p�X���b�g�Ƃ݂Ȃ��i���������j
		if (card.GetRank() == 0) continue;

		if (card.GetRank() != doubtJudgeNo_) {
			// �_�E�g����������
			return true;
		}

	}
	return false; // �_�E�g�����s����
}

void GameManager::Penalty(int penaltyPlayer)
{
	//�̂ĎD��S�ăy�i���e�B���󂯂�v���C���[�̎�D�ɉ�����
	for (int i = 0; i < discardManager_.GetDiscardCount(); ++i) {
		player_[penaltyPlayer].SetHand({ discardManager_.GetDiscard(i) });
	}
	// �̂ĎD���N���A
	discardManager_.ClearDiscard(); // �̂ĎD���N���A
	discardManager_.ClearCurrentDiscard(); // ���݂̎̂ĎD���N���A

}
