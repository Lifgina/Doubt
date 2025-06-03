#pragma once

#include "../HuEngine.h"
#include "../Class/Model/GameManager.h"
#include "../Class/View/BG.h"
#include "../Class/View/PlayerHandView.h"


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
	void CardSelect();
	void CardSelectReset();

private:
	GameManager gameManager_;
	BG bg_; // �w�i��\������N���X
	PlayerHandView playerHandView_; // �v���C���[�̎�D��\������N���X

	int myPlayerID_; // �����̃v���C���[ID
	int turnPlayerID_; // ���݂̃v���C���[ID
	int selectedCardIndex_[4]; // �I�����ꂽ�J�[�h�̃C���f�b�N�X
	int selectedCardCount_; // �I�����ꂽ�J�[�h�̖���
	bool isDiscardTurn_ ; // �̂ĎD�̃^�[�����ǂ���
	bool isInputed_; // ���͂����ꂽ���ǂ���

	float stickDeadZone_ = 0.2f; // �X�e�B�b�N�̃f�b�h�]�[��
};
