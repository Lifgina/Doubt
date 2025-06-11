//
// DoubtJudgeNoView.cpp
//

#include "DoubtJudgeNoView.h"

using namespace HE;

void DoubtJudgeNoView::Load()
{
	sprite_ = Sprite("");
	sprite_.params.siz = Math::Vector2(75.0f, 100.0f); // スプライトのサイズを設定
	font_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	font_.params.size = 36; // フォントサイズを設定
	font_.params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
	RenderingPath->AddSprite(&sprite_, 1000); // レンダリングパスに追加
	RenderingPath->AddFont(&font_, 1000); // フォントをレンダリングパスに追加
}

void DoubtJudgeNoView::Initialize()
{
	sprite_.params.pos = Math::Vector2(800.0f, 200.0f); // スプライトの位置を設定
	font_.params.posX = 800.0f+75.0f/2; // フォントの位置を設定
	font_.params.posY = 200.0f+50.0f; // フォントの位置を設定
}

void DoubtJudgeNoView::UpdateDoubtJudgeNo(int doubtJudgeNo)
{
	font_.SetText(std::to_string(doubtJudgeNo)); // ダウト判定のカード番号を表示
}