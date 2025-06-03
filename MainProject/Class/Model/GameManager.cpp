//
// GameManager.cpp
//

#include "GameManager.h"

using namespace HE;

void GameManager::Load()
{
	
}

void GameManager::Initialize()
{
	turnPlayerID_ = myPlayerID_;
	cardDistributer_.DistributeCards(player_, playerCount_);
	doubtJudgeNo_ =1;
	isDiscardTurn_ = true; // 初期状態では捨て札のターン
	isInputed_ = false; // 入力がまだされていない状態
	
}

void GameManager::Update()
{
	if (isDiscardTurn_) {
		DiscardTurn();
	}
	else {
		DoubtTurn();
	}
}
void GameManager::DiscardTurn()
{
	int discardIndex_[4] = { -1, -1, -1, -1 }; // 捨て札のインデックスを初期化
	//
	if (turnPlayerID_ == 0) {
		//isInputed_が立っていない場合はここで処理を止めておく
		if (!isInputed_) {
			return; // 入力がまだされていない場合は処理を中断
		}
		for (int i = 0; i < 4; ++i) {
			discardIndex_[i] = playerDiscardIndex_[i]; // プレイヤーが選択したカードのインデックスを取得
		}
	}
	else {
		int hands = player_[turnPlayerID_].GetPlayerHands();
		CardData handcards[52]; // 手札のカードを格納する配列
		for (int i = 0; i < hands; ++i) {
			handcards[i] = player_[turnPlayerID_].GetCard(i); // 手札のカードを取得
		}
		randomCardSelect_.CardSelect(hands,doubtJudgeNo_,handcards); // ランダムにカードを選択
		for (int i = 0; i < 4; ++i) {	
			discardIndex_[i] = randomCardSelect_.GetSelectedCardIndex(i); // 選択されたカードのインデックスを取得
		}
	}
	// 選択されたカードを捨て札に追加
	for (int i = 0; i < 4; ++i) {
		if (discardIndex_[i] != -1) {
			discardManager_.SetDiscard(player_[turnPlayerID_].GetCard(discardIndex_[i]));
			player_[turnPlayerID_].DisCard(discardIndex_[i]);
		}
	}
	isDiscardTurn_ = false; // 捨て札のターンを終了
}

void GameManager::SetPlayerDiscard(int cardIndex[])
{
	for (int i = 0; i < playerCount_; ++i) {
		playerDiscardIndex_[i] = cardIndex[i];
	}
	isInputed_ = true; // 入力されたフラグを立てる
}

void GameManager::DoubtTurn()
{
	bool isDoDoubt = false; // ダウトをするかどうかのフラグ
	if (turnPlayerID_ == 0) {
		
	}
	else {
		
	}

	if (isDoDoubt) {
		DoubtCheck();
	}

}

void GameManager::DoubtCheck()
{
	for (int i = 0; i < 4; ++i) {
		CardData card = discardManager_.GetCurrentDisCards(i);
		// rankが0の場合は未使用スロットとみなす（初期化時）
		if (card.GetRank() == 0) continue;

		if (card.GetRank() != doubtJudgeNo_) {
			
			break;
		}

	}

}

void GameManager::Penalty()
{

}
