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
	cardDiscarder_.Discard(
		player_,
		playerCount_,
		turnPlayerID_,
		myPlayerID_,
		doubtJudgeNo_,
		playerDiscardIndex_,
		isInputed_,
		discardManager_,
		randomCardSelect_,
		isInputed_,
		isDiscardTurn_
	);
}

void GameManager::SetPlayerDiscard(int cardIndex[4])
{
	for (int i = 0; i < 4; ++i) {
		playerDiscardIndex_[i] = cardIndex[i];
	}
	isInputed_ = true; // 入力されたフラグを立てる
}

void GameManager::DoubtTurn()
{
	//ダウトターンの処理
	for(int i=0;i<playerCount_;i++){
		turnPlayerID_ = (turnPlayerID_ + 1) % playerCount_; // 次のプレイヤーにターンを移す
		if (turnPlayerID_ == myPlayerID_) {
			if (!isInputed_) {
				return;
			}
		}
		else {

		}
	}

}

void GameManager::SetPlayerDoDoubt(bool isDoubt)
{
	isDoubt_ = isDoubt; // ダウトのフラグを設定
	isInputed_ = true; // 入力されたフラグを立てる
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
