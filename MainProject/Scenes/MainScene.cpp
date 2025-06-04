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
	markerView_.Load(); 

	Scene::Load();
}

// initialize a variables.
void MainScene::Initialize()
{
	myPlayerID_ = 0; // �����̃v���C���[ID��ݒ�
	gameManager_.SetMyPlayerID(myPlayerID_); // �����̃v���C���[ID��ݒ�
	gameManager_.Initialize();
	playerHandView_.UpdatePlayerHands(gameManager_.GetPlayerData(myPlayerID_)); // �����̎�D���X�V
	bg_.Initialize();

	MyPlayerCardSelectReset();
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
	if (isDiscardTurn_ && (turnPlayerID_ == myPlayerID_)) {
		MyPlayerCardSelect();
	}
	

	Scene::Update(deltaTime);
}

void MainScene::MonitorGameManager()
{
	isDiscardTurn_ = gameManager_.GetIsDiscardTurn(); // �̂ĎD�̃^�[�����ǂ������擾
	isInputed_ = gameManager_.GetIsInputed(); // ���͂����ꂽ���ǂ������擾
	turnPlayerID_ = gameManager_.GetTurnPlayerID(); // ���݂̎�Ԃ̃v���C���[ID���擾
}

void MainScene::MyPlayerCardSelect()
{
	int playerHands = gameManager_.GetPlayerData(turnPlayerID_).GetPlayerHands(); // �����̎�D�̖������擾
	HE::Gamepad gamepad_ = InputSystem.Gamepad.ElementAtOrDefault(0);
    selectingCardIndex_ ;
	markerView_.UpdateMarker(playerHandView_.GetCardPosition(selectingCardIndex_)); // �}�[�J�[�̈ʒu���X�V


	if (gamepad_.leftStick.x > stickDeadZone_ || InputSystem.Keyboard.wasPressedThisFrame.Right) {
		selectingCardIndex_ += 1; // �E�Ɉړ�
		markerView_.UpdateMarker(playerHandView_.GetCardPosition(selectingCardIndex_)); // �}�[�J�[�̈ʒu���X�V
	}
	else if (gamepad_.leftStick.x < -stickDeadZone_ || InputSystem.Keyboard.wasPressedThisFrame.Left) {
		selectingCardIndex_ -= 1; // ���Ɉړ�
		markerView_.UpdateMarker(playerHandView_.GetCardPosition(selectingCardIndex_)); // �}�[�J�[�̈ʒu���X�V
	}
	if (selectingCardIndex_ < 0)
	{
		selectingCardIndex_ = playerHands - 1; // ���[�𒴂�����E�[�ɖ߂�
		markerView_.UpdateMarker(playerHandView_.GetCardPosition(selectingCardIndex_)); // �}�[�J�[�̈ʒu���X�V
	}
	else if (selectingCardIndex_ >= playerHands)
	{
		selectingCardIndex_ = 0; // �E�[�𒴂����獶�[�ɖ߂�
		markerView_.UpdateMarker(playerHandView_.GetCardPosition(selectingCardIndex_)); // �}�[�J�[�̈ʒu���X�V
	}

	if (gamepad_.wasPressedThisFrame.Button2 || InputSystem.Keyboard.wasPressedThisFrame.Space) {
		//�Ή�����{�^���������ꂽ�Ƃ��AselectedCardIndex�̐��l��selectedCardIndex�̒l���r
		bool isAlreadySelected = false;
		for (int i = 0; i < selectedCardCount_; i++) {
			if (selectedCardIndex_[i] == selectingCardIndex_) {
				isAlreadySelected = true; // ���ɑI������Ă���J�[�h�ł���
				break;
			}
		}
		// ���ɑI������Ă���J�[�h�łȂ��ꍇ�A�I�����ꂽ�J�[�h�̃C���f�b�N�X��ۑ�

		if (!isAlreadySelected && selectedCardCount_ < 4) {
			selectedCardIndex_[selectedCardCount_] = selectingCardIndex_; // �I�����ꂽ�J�[�h�̃C���f�b�N�X��ۑ�
			selectedCardCount_++; // �I�����ꂽ�J�[�h�̖����𑝂₷
		}
		else if (isAlreadySelected) {
			// ���ɑI������Ă���J�[�h�ł���΁A�I��������
			for (int i = 0; i < selectedCardCount_; i++) {
				if (selectedCardIndex_[i] == selectingCardIndex_) {
					selectedCardIndex_[i] = selectedCardIndex_[selectedCardCount_ - 1]; // �Ō�̑I�����ꂽ�J�[�h�Ɠ���ւ���
					selectedCardCount_--; // �I�����ꂽ�J�[�h�̖��������炷
					break;
				}
			}
		}
	
	}
	if (selectedCardCount_ >= 1) {
	if (gamepad_.wasPressedThisFrame.Button1 || InputSystem.Keyboard.wasPressedThisFrame.Enter)
	{
		gameManager_.SetPlayerDiscard(selectedCardIndex_); // �I�����ꂽ�J�[�h���̂ĎD�ɐݒ�
	}
	}


}

void MainScene::MyPlayerCardSelectReset()
{
	selectingCardIndex_ = 0; // �I�𒆂̃J�[�h�̃C���f�b�N�X��������
	selectedCardCount_ = 0; // �I�����ꂽ�J�[�h�̖�����������
	for (int i = 0; i < 4; i++) {
		selectedCardIndex_[i] = -1; // �I�����ꂽ�J�[�h�̃C���f�b�N�X��������
	}
}


