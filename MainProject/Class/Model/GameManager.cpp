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
	myPlayerID_ = 0; // 自分のプレイヤーIDを設定
	discardPlayerID_ = -1; // 初期状態では捨て札を捨てたプレイヤーは未定義
	doubtplayerID_ = -1; // 初期状態ではダウトを行うプレイヤーは未定義
	isDoubt_ = false; // 初期状態ではダウトを行わない
	for (int i = 0; i < 4; i++) {
		playerDiscardIndex_[i] = -1; // 初期状態ではプレイヤーの捨て札インデックスは未定義
	}
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
    // 初回のみ: ダウト判定を始めるプレイヤーを決定
    if (doubtplayerID_ == -1) {
        doubtplayerID_ = (turnPlayerID_ + 1) % playerCount_;
        isInputed_ = false;
    }

    // 自分の番なら入力待ち
    if (doubtplayerID_ == myPlayerID_) {
        if (!isInputed_) {
            // 入力待ち
            return;
        }
    }
    else if (!isInputed_) {
        // AIのダウト判定
        int hands = player_[doubtplayerID_].GetPlayerHands();
        CardData handcards[52];
        for (int j = 0; j < hands; ++j) {
            handcards[j] = player_[doubtplayerID_].GetCard(j);
        }
        int count = 0;
        for (int j = 0; j < hands; ++j) {
            if (handcards[j].GetRank() == doubtJudgeNo_) {
                count++;
            }
        }
        float doubtProbability = 0.0f;
        if (count == 0) {
            doubtProbability = 0.05f;
        }
        else if (count == 1) {
            doubtProbability = 0.1f;
        }
        else if (count == 2) {
            doubtProbability = 0.3f;
        }
        else if (count == 3) {
            doubtProbability = 0.8f;
        }
        else {
            doubtProbability = 1.0f;
        }

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        isDoubt_ = (dist(gen) < doubtProbability);
        isInputed_ = true; // AIは即決定
    }

    // ダウト判定
    if (isInputed_) {
        if (isDoubt_) {
            if (DoubtCheck(doubtplayerID_, turnPlayerID_)) {
                Penalty(turnPlayerID_);
            }
            else {
                Penalty(doubtplayerID_);
            }
            // ターン終了処理
            doubtplayerID_ = -1;
            isDoubt_ = false;
            isInputed_ = false;
            if (player_[turnPlayerID_].GetPlayerHands() == 0) {
                winnerPlayerID_ = turnPlayerID_;
                return;
            }
            turnPlayerID_ = (turnPlayerID_ + 1) % playerCount_;
            doubtJudgeNo_ = (doubtJudgeNo_ % 13) + 1;
            isDiscardTurn_ = true;
            return;
        }
        else {
            // 次のプレイヤーへ
            doubtplayerID_ = (doubtplayerID_ + 1) % playerCount_;
            isInputed_ = false;
            // 全員スキップした場合（元のターンプレイヤーに戻った）
            if (doubtplayerID_ == turnPlayerID_) {
                doubtplayerID_ = -1;
                if (player_[turnPlayerID_].GetPlayerHands() == 0) {
                    winnerPlayerID_ = turnPlayerID_;
                    return;
                }
                turnPlayerID_ = (turnPlayerID_ + 1) % playerCount_;
                doubtJudgeNo_ = (doubtJudgeNo_ % 13) + 1;
                discardManager_.ClearCurrentDiscard();
                isDiscardTurn_ = true;
            }
        }
    }
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
    // 現在の手札を取得
    std::vector<CardData> newHand;
    int handCount = player_[penaltyPlayer].GetPlayerHands();
    for (int i = 0; i < handCount; ++i) {
        newHand.push_back(player_[penaltyPlayer].GetCard(i));
    }

    // 捨て札をすべて追加
    for (int i = 0; i < discardManager_.GetDiscardCount(); ++i) {
        newHand.push_back(discardManager_.GetDiscard(i));
    }

    // 新しい手札で上書き
    player_[penaltyPlayer].SetHand(newHand);

    // 捨て札をクリア
    discardManager_.ClearDiscard();
    discardManager_.ClearCurrentDiscard();

}
