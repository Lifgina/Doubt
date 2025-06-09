#pragma once

#include "../../HuEngine.h"
#include "CardDistributer.h"
#include "DiscardManager.h"
#include "CardDiscarder.h"
#include "RandomCardSelect.h"
#include "PlayerData.h"

/// <summary>
/// ゲームの進行を管理するクラス
/// </summary>
class GameManager {
public:
	void Load();
	void Initialize();
	void Update();
	void DiscardTurn();
	void DoubtTurn();
	void DoubtCheck();
	void Penalty();
	void SetPlayerDiscard(int cardIndex[4]);
	void SetPlayerDoDoubt(bool isDoubt);
	int SetMyPlayerID(int playerID) {
		myPlayerID_ = playerID;
		return myPlayerID_; // 設定したプレイヤーIDを返す
	}
	bool GetIsDiscardTurn() const { return isDiscardTurn_; } // 捨て札のターンかどうかを取得
	bool GetIsInputed() const { return isInputed_; } // 入力がされたかどうかを取得
	int GetTurnPlayerID() const { return turnPlayerID_; } // 現在の手番のプレイヤーIDを取得
	PlayerData GetPlayerData(int playerID) const { return player_[playerID]; } // 指定されたプレイヤーのデータを取得


private:
	int playerCount_ =4; // プレイヤーの人数
	PlayerData player_[4]; // プレイヤーのデータを管理する配列

	int playerDiscardIndex_[4]; // プレイヤーが何番目のカードを捨てたかを管理する配列

	int myPlayerID_; // 自分のプレイヤーID
	int turnPlayerID_ ; // 現在の手番のプレイヤーID
	int doubtJudgeNo_; //ダウト判定のカード番号

	bool isDiscardTurn_ ; // 捨て札を捨てる状況かどうか
	bool isInputed_ ; // 入力されたかどうか

	bool isDoubt_;

	CardDistributer cardDistributer_; // カードの管理を行うクラス
	CardDiscarder cardDiscarder_; // カードの捨てる処理を行うクラス
	DiscardManager discardManager_; // 捨て札の管理を行うクラス
	RandomCardSelect randomCardSelect_; // ランダムカード選択を行うクラス
	
};