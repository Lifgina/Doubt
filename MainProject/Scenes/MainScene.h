#pragma once

#include "../HuEngine.h"
#include "../Class/Model/GameManager.h"
#include "../Class/View/BG.h"
#include "../Class/View/PlayerHandView.h"
#include "../Class/View/MarkerView.h"
#include "../Class/View/CheckerView.h"
#include "../Class/View/CardCountView.h"
#include "../Class/View/WinnerView.h"
#include "../Class/View/PlayerDoubtView.h"


class MainScene : public HE::Scene
{
public:
	MainScene();
	virtual ~MainScene() { Terminate(); }

	void ResizeLayout() override;

	void Load() override;
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;

	void MonitorGameManager();
	void MyPlayerCardSelect();
	void MyPlayerCardSelectReset();
	void MyDoubtSelect();
	

private:
	GameManager gameManager_;
	BG bg_; // 背景を表示するクラス
	PlayerHandView playerHandView_; // プレイヤーの手札を表示するクラス
	MarkerView markerView_; // マーカーを表示するクラス
	CheckerView checkerView_[4]; // チェッカーを表示するクラス
	CardcountView cardCountView_[4]; // カードの枚数を表示するクラス
	WinnerView winnerView_; // 勝者を表示するクラス
	PlayerDoubtView playerDoubtView_; // ダウトのメニューを表示するクラス

	int myPlayerID_; // 自分のプレイヤーID
	int turnPlayerID_; // 現在のプレイヤーID
	int doubtPlayerID_; // ダウトを行うプレイヤーのID
	int winnerID_; // 勝者のプレイヤーID
	int selectingCardIndex_; // 選択中のカードのインデックス
	int selectedCardIndex_[4]; // 選択されたカードのインデックス
	int selectedCardCount_; // 選択されたカードの枚数
	bool isDiscardTurn_ ; // 捨て札のターンかどうか
	bool isInputed_; // 入力がされたかどうか

	float stickDeadZone_ = 0.2f; // スティックのデッドゾーン
};
