//
// MainScene.cpp
//

#include "MainScene.h"

using namespace HE;

// initialize member variables.
MainScene::MainScene()
{

}

// rearrange UI to fit the size.
void MainScene::ResizeLayout()
{
	Scene::ResizeLayout();



}

// load resources.
void MainScene::Load()
{
	gameManager_.Load();
	playerHandView_.Load();
	bg_.Load();

	Scene::Load();
}

// initialize a variables.
void MainScene::Initialize()
{
	gameManager_.Initialize();
	playerHandView_.Initialize();
	bg_.Initialize();

	CardSelectReset();
}

// releasing resources required for termination.
void MainScene::Terminate()
{

}

// updates the scene.
void MainScene::Update(float deltaTime)
{
	gameManager_.Update();
	MonitorGameManager();
	if (isDiscardTurn_ && (turnPlayerID_ == 0)) {
		CardSelect();
	}
	

	Scene::Update(deltaTime);
}

void MainScene::MonitorGameManager()
{
	isDiscardTurn_ = gameManager_.GetIsDiscardTurn(); // �̂ĎD�̃^�[�����ǂ������擾
	isInputed_ = gameManager_.GetIsInputed(); // ���͂����ꂽ���ǂ������擾
	turnPlayerID_ = gameManager_.GetTurnPlayerID(); // ���݂̎�Ԃ̃v���C���[ID���擾
}

void MainScene::CardSelect()
{
	int playerHands = gameManager_.GetMyPlayerHands(); // �����̎�D�̖������擾
	HE::Gamepad gamepad_ = InputSystem.Gamepad.ElementAtOrDefault(0);
	int selectingCardIndex = 0;

	if (gamepad_.leftStick.x > stickDeadZone_ || InputSystem.Keyboard.isPressed.Right) {
		selectingCardIndex += 1; // �E�Ɉړ�
	}
	else if (gamepad_.leftStick.x < -stickDeadZone_ || InputSystem.Keyboard.isPressed.Left) {
		selectingCardIndex -= 1; // ���Ɉړ�
	}
	if (selectingCardIndex < 0)
	{
		selectingCardIndex = playerHands - 1; // ���[�𒴂�����E�[�ɖ߂�
	}
	else if (selectingCardIndex >= playerHands)
	{
		selectingCardIndex = 0; // �E�[�𒴂����獶�[�ɖ߂�
	}

	if (gamepad_.wasPressedThisFrame.Button2 || InputSystem.Keyboard.wasPressedThisFrame.Space) {
		//�Ή�����{�^���������ꂽ�Ƃ��AselectedCardIndex�̐��l��selectedCardIndex�̒l���r
		bool isAlreadySelected = false;
		for (int i = 0; i < selectedCardCount_; i++) {
			if (selectedCardIndex_[i] == selectingCardIndex) {
				isAlreadySelected = true; // ���ɑI������Ă���J�[�h�ł���
				break;
			}
		}
		// ���ɑI������Ă���J�[�h�łȂ��ꍇ�A�I�����ꂽ�J�[�h�̃C���f�b�N�X��ۑ�

		if (!isAlreadySelected && selectedCardCount_ < 4) {
			selectedCardIndex_[selectedCardCount_] = selectingCardIndex; // �I�����ꂽ�J�[�h�̃C���f�b�N�X��ۑ�
			selectedCardCount_++; // �I�����ꂽ�J�[�h�̖����𑝂₷
		}
		else if (isAlreadySelected) {
			// ���ɑI������Ă���J�[�h�ł���΁A�I��������
			for (int i = 0; i < selectedCardCount_; i++) {
				if (selectedCardIndex_[i] == selectingCardIndex) {
					selectedCardIndex_[i] = selectedCardIndex_[selectedCardCount_ - 1]; // �Ō�̑I�����ꂽ�J�[�h�Ɠ���ւ���
					selectedCardCount_--; // �I�����ꂽ�J�[�h�̖��������炷
					break;
				}
			}
		}
	
	}



}

void MainScene::CardSelectReset()
{
	selectedCardCount_ = 0; // �I�����ꂽ�J�[�h�̖�����������
	for (int i = 0; i < 4; i++) {
		selectedCardIndex_[i] = -1; // �I�����ꂽ�J�[�h�̃C���f�b�N�X��������
	}
}

