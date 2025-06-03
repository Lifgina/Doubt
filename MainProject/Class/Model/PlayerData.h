#pragma once

#include "../../HuEngine.h"
#include "CardData.h"

class PlayerData {
public:
    int GetPlayerID() const { return playerID_; }
    void SetPlayerID(int id) { playerID_ = id; }
    void SetHand(const std::vector<CardData>& hand);
	int GetPlayerHands() const { return playerHands_; }
	CardData GetCard(int index) const { return hand_[index]; } // ��D�̃J�[�h���擾
    void DisCard(int index);
	

private:
    int playerID_; // �v���C���[��ID
    int playerHands_; // �v���C���[�̎�D�̖���
    CardData hand_[52]; // �v���C���[�̎�D�i�ő�52���j
};
