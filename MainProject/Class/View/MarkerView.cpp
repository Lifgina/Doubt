//
// ClassTemplete.cpp
//

#include "MarkerView.h"

using namespace HE;

void MarkerView::Load()
{
	markerSprite_ = Sprite("Marker.png");
	RenderingPath->AddSprite(&markerSprite_, 0); // レンダリングパスに追加
	markerSprite_.params.siz = Math::Vector2(25.0f, 25.0f); // マーカーのサイズを設定
	markerSprite_.params.pos = Math::Vector2(-1000.0f, 0.0f); // 初期位置を設定

}

void MarkerView::UpdateMarker(Math::Vector2 cardpos)
{
	markerSprite_.params.pos = Math::Vector2(cardpos.x+75.0f/8, cardpos.y-25.0f); // マーカーの位置を更新
	
}

void MarkerView::MarkerDelete()
{
	markerSprite_.params.pos = Math::Vector2(-1000.0f, 0.0f); // マーカーの位置を初期化
}
