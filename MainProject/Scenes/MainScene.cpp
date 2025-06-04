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
	myPlayerID_ = 0; // 自分のプレイヤーIDを設定
	gameManager_.SetMyPlayerID(myPlayerID_); // 自分のプレイヤーIDを設定
	gameManager_.Initialize();
	playerHandView_.UpdatePlayerHands(gameManager_.GetPlayerData(myPlayerID_)); // 自分の手札を更新
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
	isDiscardTurn_ = gameManager_.GetIsDiscardTurn(); // 捨て札のターンかどうかを取得
	isInputed_ = gameManager_.GetIsInputed(); // 入力がされたかどうかを取得
	turnPlayerID_ = gameManager_.GetTurnPlayerID(); // 現在の手番のプレイヤーIDを取得
}

void MainScene::MyPlayerCardSelect()
{
	int playerHands = gameManager_.GetPlayerData(turnPlayerID_).GetPlayerHands(); // 自分の手札の枚数を取得
	HE::Gamepad gamepad_ = InputSystem.Gamepad.ElementAtOrDefault(0);
    selectingCardIndex_ ;
	markerView_.UpdateMarker(playerHandView_.GetCardPosition(selectingCardIndex_)); // マーカーの位置を更新


	if (gamepad_.leftStick.x > stickDeadZone_ || InputSystem.Keyboard.wasPressedThisFrame.Right) {
		selectingCardIndex_ += 1; // 右に移動
		markerView_.UpdateMarker(playerHandView_.GetCardPosition(selectingCardIndex_)); // マーカーの位置を更新
	}
	else if (gamepad_.leftStick.x < -stickDeadZone_ || InputSystem.Keyboard.wasPressedThisFrame.Left) {
		selectingCardIndex_ -= 1; // 左に移動
		markerView_.UpdateMarker(playerHandView_.GetCardPosition(selectingCardIndex_)); // マーカーの位置を更新
	}
	if (selectingCardIndex_ < 0)
	{
		selectingCardIndex_ = playerHands - 1; // 左端を超えたら右端に戻る
		markerView_.UpdateMarker(playerHandView_.GetCardPosition(selectingCardIndex_)); // マーカーの位置を更新
	}
	else if (selectingCardIndex_ >= playerHands)
	{
		selectingCardIndex_ = 0; // 右端を超えたら左端に戻る
		markerView_.UpdateMarker(playerHandView_.GetCardPosition(selectingCardIndex_)); // マーカーの位置を更新
	}

	if (gamepad_.wasPressedThisFrame.Button2 || InputSystem.Keyboard.wasPressedThisFrame.Space) {
		//対応するボタンが押されたとき、selectedCardIndexの数値とselectedCardIndexの値を比較
		bool isAlreadySelected = false;
		for (int i = 0; i < selectedCardCount_; i++) {
			if (selectedCardIndex_[i] == selectingCardIndex_) {
				isAlreadySelected = true; // 既に選択されているカードである
				break;
			}
		}
		// 既に選択されているカードでない場合、選択されたカードのインデックスを保存

		if (!isAlreadySelected && selectedCardCount_ < 4) {
			selectedCardIndex_[selectedCardCount_] = selectingCardIndex_; // 選択されたカードのインデックスを保存
			selectedCardCount_++; // 選択されたカードの枚数を増やす
		}
		else if (isAlreadySelected) {
			// 既に選択されているカードであれば、選択を解除
			for (int i = 0; i < selectedCardCount_; i++) {
				if (selectedCardIndex_[i] == selectingCardIndex_) {
					selectedCardIndex_[i] = selectedCardIndex_[selectedCardCount_ - 1]; // 最後の選択されたカードと入れ替える
					selectedCardCount_--; // 選択されたカードの枚数を減らす
					break;
				}
			}
		}
	
	}
	if (selectedCardCount_ >= 1) {
	if (gamepad_.wasPressedThisFrame.Button1 || InputSystem.Keyboard.wasPressedThisFrame.Enter)
	{
		gameManager_.SetPlayerDiscard(selectedCardIndex_); // 選択されたカードを捨て札に設定
	}
	}


}

void MainScene::MyPlayerCardSelectReset()
{
	selectingCardIndex_ = 0; // 選択中のカードのインデックスを初期化
	selectedCardCount_ = 0; // 選択されたカードの枚数を初期化
	for (int i = 0; i < 4; i++) {
		selectedCardIndex_[i] = -1; // 選択されたカードのインデックスを初期化
	}
}


