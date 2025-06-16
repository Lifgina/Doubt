//
// WinnerView.cpp
//

#include "WinnerView.h"

using namespace HE;

void WinnerView::Load()
{
	for (int i = 0; i < 2; i++) {
		winnerFont_[i].params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
		winnerFont_[i].params.size = 36; // フォントサイズを設定
		winnerFont_[i].params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
		RenderingPath->AddFont(&winnerFont_[i], 1000); // レンダリングパスに追加
	}
	winnerFont_[0].params.posX = 800.0f; // 勝者表示の位置を設定
	winnerFont_[0].params.posY = 360.0f; // 勝者表示の位置を設定
	winnerFont_[1].params.posX = 800.0f; // 勝者表示の位置を設定
	winnerFont_[1].params.posY = 400.0f; // 勝者表示の位置を設定
	toTitleFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	toTitleFont_.params.size = 24; // タイトルへ戻るフォントのサイズを設定
	toTitleFont_.params.color = Color(0.0f, 0.0f, 0.0f); // タイトルへ戻るフォントの色を設定
	toTitleFont_.params.posX = 640.0f; // タイトルへ戻るフォントの位置を設定
	toTitleFont_.params.posY = 600.0f; // タイトルへ戻るフォントの位置を設定
	RenderingPath->AddFont(&toTitleFont_, 1000); // タイトルへ戻るフォントをレンダリングパスに追加

	
}


void WinnerView::ShowWinner(int winnerID)
{
	if (winnerID < 0 || winnerID >= 4) {
		return; // 無効なプレイヤーID
	}
	winnerFont_[0].SetText(L"Winner: Player " + std::to_wstring(winnerID + 1)); // 勝者のプレイヤーIDを表示
	winnerFont_[1].SetText(L"Congratulations!"); // おめでとうメッセージを表示
	toTitleFont_.SetText(L"決定ボタンでタイトルへ戻る"); // タイトルへ戻るメッセージを表示
	
	

}