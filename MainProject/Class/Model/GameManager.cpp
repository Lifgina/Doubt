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
	myPlayerID_ = 0; // �����̃v���C���[ID��ݒ�
	discardPlayerID_ = -1; // ������Ԃł͎̂ĎD���̂Ă��v���C���[�͖���`
	doubtplayerID_ = -1; // ������Ԃł̓_�E�g���s���v���C���[�͖���`
	isDoubt_ = false; // ������Ԃł̓_�E�g���s��Ȃ�
	for (int i = 0; i < 4; i++) {
		playerDiscardIndex_[i] = -1; // ������Ԃł̓v���C���[�̎̂ĎD�C���f�b�N�X�͖���`
	}
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
    // ����̂�: �_�E�g������n�߂�v���C���[������
    if (doubtplayerID_ == -1) {
        doubtplayerID_ = (turnPlayerID_ + 1) % playerCount_;
        isInputed_ = false;
    }

    // �����̔ԂȂ���͑҂�
    if (doubtplayerID_ == myPlayerID_) {
        if (!isInputed_) {
            // ���͑҂�
            return;
        }
    }
    else if (!isInputed_) {
        // AI�̃_�E�g����
        int hands = player_[doubtplayerID_].GetPlayerHands();
        CardData handcards[52];
        for (int j = 0; j < hands; ++j) {
            handcards[j] = player_[doubtplayerID_].GetCard(j);
        }
        int count = 0;
        for (int j = 0; j < hands; ++j) {
            if (handcards[j].GetRank() == doubtJudgeNo_) {
                count++;
            }
        }
        float doubtProbability = 0.0f;
        if (count == 0) {
            doubtProbability = 0.05f;
        }
        else if (count == 1) {
            doubtProbability = 0.1f;
        }
        else if (count == 2) {
            doubtProbability = 0.3f;
        }
        else if (count == 3) {
            doubtProbability = 0.8f;
        }
        else {
            doubtProbability = 1.0f;
        }

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        isDoubt_ = (dist(gen) < doubtProbability);
        isInputed_ = true; // AI�͑�����
    }

    // �_�E�g����
    if (isInputed_) {
        if (isDoubt_) {
            if (DoubtCheck(doubtplayerID_, turnPlayerID_)) {
                Penalty(turnPlayerID_);
            }
            else {
                Penalty(doubtplayerID_);
            }
            // �^�[���I������
            doubtplayerID_ = -1;
            isDoubt_ = false;
            isInputed_ = false;
            if (player_[turnPlayerID_].GetPlayerHands() == 0) {
                winnerPlayerID_ = turnPlayerID_;
                return;
            }
            turnPlayerID_ = (turnPlayerID_ + 1) % playerCount_;
            doubtJudgeNo_ = (doubtJudgeNo_ % 13) + 1;
            isDiscardTurn_ = true;
            return;
        }
        else {
            // ���̃v���C���[��
            doubtplayerID_ = (doubtplayerID_ + 1) % playerCount_;
            isInputed_ = false;
            // �S���X�L�b�v�����ꍇ�i���̃^�[���v���C���[�ɖ߂����j
            if (doubtplayerID_ == turnPlayerID_) {
                doubtplayerID_ = -1;
                if (player_[turnPlayerID_].GetPlayerHands() == 0) {
                    winnerPlayerID_ = turnPlayerID_;
                    return;
                }
                turnPlayerID_ = (turnPlayerID_ + 1) % playerCount_;
                doubtJudgeNo_ = (doubtJudgeNo_ % 13) + 1;
                discardManager_.ClearCurrentDiscard();
                isDiscardTurn_ = true;
            }
        }
    }
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
    // ���݂̎�D���擾
    std::vector<CardData> newHand;
    int handCount = player_[penaltyPlayer].GetPlayerHands();
    for (int i = 0; i < handCount; ++i) {
        newHand.push_back(player_[penaltyPlayer].GetCard(i));
    }

    // �̂ĎD�����ׂĒǉ�
    for (int i = 0; i < discardManager_.GetDiscardCount(); ++i) {
        newHand.push_back(discardManager_.GetDiscard(i));
    }

    // �V������D�ŏ㏑��
    player_[penaltyPlayer].SetHand(newHand);

    // �̂ĎD���N���A
    discardManager_.ClearDiscard();
    discardManager_.ClearCurrentDiscard();

}
