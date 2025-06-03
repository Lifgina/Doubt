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
	isDiscardTurn_ = gameManager_.GetIsDiscardTurn(); // 捨て札のターンかどうかを取得
	isInputed_ = gameManager_.GetIsInputed(); // 入力がされたかどうかを取得
	turnPlayerID_ = gameManager_.GetTurnPlayerID(); // 現在の手番のプレイヤーIDを取得
}

void MainScene::CardSelect()
{
	int playerHands = gameManager_.GetMyPlayerHands(); // 自分の手札の枚数を取得
	HE::Gamepad gamepad_ = InputSystem.Gamepad.ElementAtOrDefault(0);
	int selectingCardIndex = 0;

	if (gamepad_.leftStick.x > stickDeadZone_ || InputSystem.Keyboard.isPressed.Right) {
		selectingCardIndex += 1; // 右に移動
	}
	else if (gamepad_.leftStick.x < -stickDeadZone_ || InputSystem.Keyboard.isPressed.Left) {
		selectingCardIndex -= 1; // 左に移動
	}
	if (selectingCardIndex < 0)
	{
		selectingCardIndex = playerHands - 1; // 左端を超えたら右端に戻る
	}
	else if (selectingCardIndex >= playerHands)
	{
		selectingCardIndex = 0; // 右端を超えたら左端に戻る
	}

	if (gamepad_.wasPressedThisFrame.Button2 || InputSystem.Keyboard.wasPressedThisFrame.Space) {
		//対応するボタンが押されたとき、selectedCardIndexの数値とselectedCardIndexの値を比較
		bool isAlreadySelected = false;
		for (int i = 0; i < selectedCardCount_; i++) {
			if (selectedCardIndex_[i] == selectingCardIndex) {
				isAlreadySelected = true; // 既に選択されているカードである
				break;
			}
		}
		// 既に選択されているカードでない場合、選択されたカードのインデックスを保存

		if (!isAlreadySelected && selectedCardCount_ < 4) {
			selectedCardIndex_[selectedCardCount_] = selectingCardIndex; // 選択されたカードのインデックスを保存
			selectedCardCount_++; // 選択されたカードの枚数を増やす
		}
		else if (isAlreadySelected) {
			// 既に選択されているカードであれば、選択を解除
			for (int i = 0; i < selectedCardCount_; i++) {
				if (selectedCardIndex_[i] == selectingCardIndex) {
					selectedCardIndex_[i] = selectedCardIndex_[selectedCardCount_ - 1]; // 最後の選択されたカードと入れ替える
					selectedCardCount_--; // 選択されたカードの枚数を減らす
					break;
				}
			}
		}
	
	}



}

void MainScene::CardSelectReset()
{
	selectedCardCount_ = 0; // 選択されたカードの枚数を初期化
	for (int i = 0; i < 4; i++) {
		selectedCardIndex_[i] = -1; // 選択されたカードのインデックスを初期化
	}
}

