#pragma once

#include "../HuEngine.h"
#include "../Class/Model/GameManager.h"
#include "../Class/View/BG.h"
#include "../Class/View/PlayerHandView.h"
#include "../Class/View/MarkerView.h"
#include "../Class/View/CheckerView.h"
#include "../Class/View/CardCountView.h"
#include "../Class/View/WinnerView.h"
#include "../Class/View/PlayerDoubtView.h"
#include "../Class/View/DoubtJudgeNoView.h"
#include "../Class/View/DiscardView.h"


class MainScene : public HE::Scene
{
public:
	MainScene();
	virtual ~MainScene() { Terminate(); }

	void ResizeLayout() override;

	void Load() override;
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;

	void MonitorGameManager();
	void MonitorDiscard();
	void MyPlayerCardSelect();
	void MyPlayerCardSelectReset();
	void MyDoubtSelect();
	

private:
	GameManager gameManager_;
	BG bg_; // �w�i��\������N���X
	PlayerHandView playerHandView_; // �v���C���[�̎�D��\������N���X
	MarkerView markerView_; // �}�[�J�[��\������N���X
	CheckerView checkerView_[4]; // �`�F�b�J�[��\������N���X
	CardcountView cardCountView_[4]; // �J�[�h�̖�����\������N���X
	WinnerView winnerView_; // ���҂�\������N���X
	PlayerDoubtView playerDoubtView_; // �_�E�g�̃��j���[��\������N���X
	DoubtJudgeNoView doubtJudgeNoView_; // �_�E�g����̃J�[�h�ԍ���\������N���X
	DiscardView discardView_; // �̂ĎD��\������N���X

	int playerCount_; // �v���C���[�̐l��
	int myPlayerID_; // �����̃v���C���[ID
	int turnPlayerID_; // ���݂̃v���C���[ID
	int doubtPlayerID_; // �_�E�g���s���v���C���[��ID
	int winnerID_; // ���҂̃v���C���[ID
	int doubtJudgeNo_; // �_�E�g����̃J�[�h�ԍ�
	int selectingCardIndex_; // �I�𒆂̃J�[�h�̃C���f�b�N�X
	int selectedCardIndex_[4]; // �I�����ꂽ�J�[�h�̃C���f�b�N�X
	int selectedCardCount_; // �I�����ꂽ�J�[�h�̖���
	int prevDiscardCount_ ; // �O��̎̂ĎD�̖���
	int prevPlayerHands_; // �O�t���[���̃v���C���[�̎�D�̖���
	bool isDiscardTurn_ ; // �̂ĎD�̃^�[�����ǂ���
	bool isInputed_; // ���͂����ꂽ���ǂ���

	float stickDeadZone_ = 0.2f; // �X�e�B�b�N�̃f�b�h�]�[��
};
