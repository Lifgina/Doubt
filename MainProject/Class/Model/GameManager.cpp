//
// GameManager.cpp
//

#include "GameManager.h"
#include <random>

using namespace HE;

void GameManager::Load()
{
	
}

void GameManager::Initialize()
{
	turnPlayerID_ = myPlayerID_;
	cardDistributer_.DistributeCards(player_, playerCount_);
	doubtJudgeNo_ =1;
	winnerPlayerID_ = -1; // 初期状態では勝者は未定義
	isDiscardTurn_ = true; // 初期状態では捨て札のターン
	isInputed_ = false; // 入力がまだされていない状態
	
}

void GameManager::Update()
{
	if (winnerPlayerID_ != -1) {
		return; // 勝者が決まっている場合は何もしない
	}
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
	doubtplayerID_ = turnPlayerID_ ; // ダウトを行うプレイヤーのID
	//ダウトターンの処理
	for(int i=0;i<playerCount_;i++){
		doubtplayerID_ = (doubtplayerID_ + 1) % playerCount_; // 次のプレイヤーにターンを移す
		if (doubtplayerID_ == myPlayerID_) {
			if (!isInputed_) {
				return;
			}
		}
		else {
			//プレイヤーの手札を取得
			int hands = player_[doubtplayerID_].GetPlayerHands();
			CardData handcards[52];
			for (int j = 0; j < hands; ++j) {
				handcards[j] = player_[doubtplayerID_].GetCard(j);
			}
			//doubtJudgeNoのカードが何枚あるかをカウント
			int count = 0;
			for (int j = 0; j < hands; ++j) {
				if (handcards[j].GetRank() == doubtJudgeNo_) {
					count++;
				}
			}
			//countの値に応じた確率で、ダウトをするかどうかを決める
			float doubtProbability = 0.0f;
			if (count == 0) {
				doubtProbability = 0.05f; // 0枚なら高確率でダウト
			}
			else if (count == 1) {
				doubtProbability = 0.1f;
			}
			else if (count == 2) {
				doubtProbability = 0.3f;
			}
			else if(count == 3){
				doubtProbability = 0.8f; 
			}
			else {
				doubtProbability = 1.0f; // 4枚なら必ずダウト
			}

			// 乱数生成
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_real_distribution<float> dist(0.0f, 1.0f);

			if (dist(gen) < doubtProbability) {
				isDoubt_ = true; // ダウトするフラグを立てる
			}
			else {
				isDoubt_ = false; // ダウトしないフラグを立てる
			}

		}
		// ダウトチェックを行い、成功したら即座にDoubtTurnも終了
		if (isDoubt_)
		{
			if (DoubtCheck(doubtplayerID_, turnPlayerID_)) {
				Penalty(turnPlayerID_); // ダウトが成功した場合、手札を捨てたプレイヤーにペナルティを与える
				isDoubt_ = false; // ダウトフラグをリセット
				isInputed_ = false; // 入力フラグをリセット
				
			}
			else {
				Penalty(doubtplayerID_); // ダウトが失敗した場合、ダウトしたプレイヤーにペナルティを与える
			}
		}
		
	}
	// ダウトターンが終了した時、ターンプレイヤーの手札が0枚になった場合、勝者を設定
	if (player_[turnPlayerID_].GetPlayerHands() == 0) {
		winnerPlayerID_ = turnPlayerID_; // 勝者を設定
		return; // 勝者が決まったので終了
	}
	turnPlayerID_ = (turnPlayerID_ + 1) % playerCount_; // 次のプレイヤーにターンを移す
	doubtJudgeNo_ = (doubtJudgeNo_ % 13) + 1; // ダウト判定のカード番号を次の番号に更新（1-13の範囲で循環）
	isDiscardTurn_ = true; // ダウトターンが終了したら、次は捨て札のターンにする

}

void GameManager::SetPlayerDoDoubt(bool isDoubt)
{
	isDoubt_ = isDoubt; // ダウトのフラグを設定
	isInputed_ = true; // 入力されたフラグを立てる
}

bool GameManager::DoubtCheck(int doubtPlayerID,int discardPlayerID)
{
	for (int i = 0; i < 4; ++i) {
		CardData card = discardManager_.GetCurrentDisCards(i);
		// rankが0の場合は未使用スロットとみなす（初期化時）
		if (card.GetRank() == 0) continue;

		if (card.GetRank() != doubtJudgeNo_) {
			// ダウトが成功した
			return true;
		}

	}
	return false; // ダウトが失敗した
}

void GameManager::Penalty(int penaltyPlayer)
{
	//捨て札を全てペナルティを受けるプレイヤーの手札に加える
	for (int i = 0; i < discardManager_.GetDiscardCount(); ++i) {
		player_[penaltyPlayer].SetHand({ discardManager_.GetDiscard(i) });
	}
	// 捨て札をクリア
	discardManager_.ClearDiscard(); // 捨て札をクリア
	discardManager_.ClearCurrentDiscard(); // 現在の捨て札をクリア

}
