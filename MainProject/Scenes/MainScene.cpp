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
	winnerView_.Load(); 
	for (int i = 0; i < 4; i++) {
		checkerView_[i].Load(); 
	}
	for  (int i = 0; i < 4; i++) {
		cardCountView_[i].Load(); // �J�[�h�̖�����\������N���X�̃��[�h
	}
	

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
	cardCountView_[0].Initialize(Math::Vector2(800.0f,360.0f)); 
	cardCountView_[1].Initialize(Math::Vector2(10.0, 200.0f));
	cardCountView_[2].Initialize(Math::Vector2(400.0f, 10.0f));
	cardCountView_[3].Initialize(Math::Vector2(1170.0f, 200.0f));

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
	if (winnerID_ != -1) {
		winnerView_.ShowWinner(winnerID_); // ���҂�\��
		//�����Ɍ�Ń^�C�g���֖߂鏈����ǉ�����
		return; // ���҂����܂����̂ŏI��
	}
	if (isDiscardTurn_ && (turnPlayerID_ == myPlayerID_)) {
		MyPlayerCardSelect();
	}
	else if(doubtPlayerID_ == myPlayerID_){
		MyDoubtSelect();
	}
	else
	{
		playerHandView_.UpdatePlayerHands(gameManager_.GetPlayerData(myPlayerID_)); // �����̎�D���X�V
	}

	for (int i = 0; i < 4; i++) {
		cardCountView_[i].UpdateCardcount(gameManager_.GetPlayerData(i).GetPlayerHands()); // �J�[�h�̖������X�V
	}
	

	Scene::Update(deltaTime);
}

void MainScene::MonitorGameManager()
{
	isDiscardTurn_ = gameManager_.GetIsDiscardTurn(); // �̂ĎD�̃^�[�����ǂ������擾
	isInputed_ = gameManager_.GetIsInputed(); // ���͂����ꂽ���ǂ������擾
	turnPlayerID_ = gameManager_.GetTurnPlayerID(); // ���݂̎�Ԃ̃v���C���[ID���擾
	doubtPlayerID_ = gameManager_.GetDoubtPlayerID(); // �_�E�g���s���v���C���[��ID���擾
	winnerID_ = gameManager_.GetWinnerPlayerID(); // ���҂̃v���C���[ID���擾
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
			checkerView_[selectedCardCount_].UpdateChecker(playerHandView_.GetCardPosition(selectingCardIndex_)); // �`�F�b�J�[�̈ʒu���X�V
			selectedCardIndex_[selectedCardCount_] = selectingCardIndex_; // �I�����ꂽ�J�[�h�̃C���f�b�N�X��ۑ�
			selectedCardCount_++; // �I�����ꂽ�J�[�h�̖����𑝂₷
		}
		else if (isAlreadySelected) {
			// ���ɑI������Ă���J�[�h�ł���΁A�I��������
			for (int i = 0; i < selectedCardCount_; i++) {
				if (selectedCardIndex_[i] == selectingCardIndex_) {
					// �Ō�̃`�F�b�J�[�����݂̈ʒu�Ɉړ�
					if (i != selectedCardCount_ - 1) {
						checkerView_[i].UpdateChecker(playerHandView_.GetCardPosition(selectedCardIndex_[selectedCardCount_ - 1]));
					}
					checkerView_[selectedCardCount_ - 1].CheckerDelete(); // �Ō�̃`�F�b�J�[���폜

					// �z����Ō�̗v�f�ŏ㏑��
					selectedCardIndex_[i] = selectedCardIndex_[selectedCardCount_ - 1];
					selectedCardCount_--;
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

void MainScene::MyDoubtSelect()
{
	playerDoubtView_.ShowDoubtMenu(); // �_�E�g���j���[��\��
	HE::Gamepad gamepad_ = InputSystem.Gamepad.ElementAtOrDefault(0);
	if (gamepad_.leftStick.y>=0.3 || InputSystem.Keyboard.wasPressedThisFrame.Up) {
		playerDoubtView_.HideDoubtMenu(); // �_�E�g���j���[���\��
		gameManager_.SetPlayerDoDoubt(true); // �_�E�g���s��
	}
	else if (gamepad_.leftStick.y<=-0.3 || InputSystem.Keyboard.wasPressedThisFrame.Down) {
		playerDoubtView_.HideDoubtMenu(); // �_�E�g���j���[���\��
		gameManager_.SetPlayerDoDoubt(false); // �_�E�g���s��Ȃ�
	}
}

