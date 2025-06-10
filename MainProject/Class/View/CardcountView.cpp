//
// CardcountView.cpp
//

#include "CardcountView.h"

using namespace HE;

void CardcountView::Load()
{
	cardBackSprite_ = Sprite("");
	RenderingPath->AddSprite(&cardBackSprite_, 0); // レンダリングパスに追加
	cardCountsFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	cardCountsFont_.params.size = 36; // フォントサイズを設定
	cardCountsFont_.params.color = Color(0.0f, 0.0f, 0.0f); // フォントの色を設定
	RenderingPath->AddFont(&cardCountsFont_, 1000); // レンダリングパスに追加
}

void CardcountView::Initialize(Math::Vector2 position)
{
	cardBackSprite_.params.pos = position; // カードの裏面の位置を設定
	cardBackSprite_.params.siz = Math::Vector2(75.0f, 100.0f); // カードのサイズを設定
	cardCountsFont_.params.posX = position.x + 75.0f/2-18; // カードの枚数表示の位置を設定
	cardCountsFont_.params.posY = position.y + 100.0f/2-18; // カードの枚数表示の位置を設定

}

void CardcountView::UpdateCardcount(int playerCardcount)
{
	cardCountsFont_.SetText(std::to_string(playerCardcount));
}