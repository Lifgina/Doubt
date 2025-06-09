#pragma once

#include "../../HuEngine.h"
#include "CardDistributer.h"
#include "DiscardManager.h"
#include "CardDiscarder.h"
#include "RandomCardSelect.h"
#include "PlayerData.h"

/// <summary>
/// �Q�[���̐i�s���Ǘ�����N���X
/// </summary>
class GameManager {
public:
	void Load();
	void Initialize();
	void Update();
	void DiscardTurn();
	void DoubtTurn();
	void DoubtCheck();
	void Penalty();
	void SetPlayerDiscard(int cardIndex[4]);
	void SetPlayerDoDoubt(bool isDoubt);
	int SetMyPlayerID(int playerID) {
		myPlayerID_ = playerID;
		return myPlayerID_; // �ݒ肵���v���C���[ID��Ԃ�
	}
	bool GetIsDiscardTurn() const { return isDiscardTurn_; } // �̂ĎD�̃^�[�����ǂ������擾
	bool GetIsInputed() const { return isInputed_; } // ���͂����ꂽ���ǂ������擾
	int GetTurnPlayerID() const { return turnPlayerID_; } // ���݂̎�Ԃ̃v���C���[ID���擾
	PlayerData GetPlayerData(int playerID) const { return player_[playerID]; } // �w�肳�ꂽ�v���C���[�̃f�[�^���擾


private:
	int playerCount_ =4; // �v���C���[�̐l��
	PlayerData player_[4]; // �v���C���[�̃f�[�^���Ǘ�����z��

	int playerDiscardIndex_[4]; // �v���C���[�����Ԗڂ̃J�[�h���̂Ă������Ǘ�����z��

	int myPlayerID_; // �����̃v���C���[ID
	int turnPlayerID_ ; // ���݂̎�Ԃ̃v���C���[ID
	int doubtJudgeNo_; //�_�E�g����̃J�[�h�ԍ�

	bool isDiscardTurn_ ; // �̂ĎD���̂Ă�󋵂��ǂ���
	bool isInputed_ ; // ���͂��ꂽ���ǂ���

	bool isDoubt_;

	CardDistributer cardDistributer_; // �J�[�h�̊Ǘ����s���N���X
	CardDiscarder cardDiscarder_; // �J�[�h�̎̂Ă鏈�����s���N���X
	DiscardManager discardManager_; // �̂ĎD�̊Ǘ����s���N���X
	RandomCardSelect randomCardSelect_; // �����_���J�[�h�I�����s���N���X
	
};