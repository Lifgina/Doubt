//
// ClassTemplete.cpp
//

#include "MarkerView.h"

using namespace HE;

void MarkerView::Load()
{
	markerSprite_ = Sprite("Marker.png");
	RenderingPath->AddSprite(&markerSprite_, 0); // �����_�����O�p�X�ɒǉ�
	markerSprite_.params.siz = Math::Vector2(25.0f, 25.0f); // �}�[�J�[�̃T�C�Y��ݒ�
	markerSprite_.params.pos = Math::Vector2(-1000.0f, 0.0f); // �����ʒu��ݒ�

}

void MarkerView::UpdateMarker(Math::Vector2 cardpos)
{
	markerSprite_.params.pos = Math::Vector2(cardpos.x+75.0f/8, cardpos.y-25.0f); // �}�[�J�[�̈ʒu���X�V
	
}

void MarkerView::MarkerDelete()
{
	markerSprite_.params.pos = Math::Vector2(-1000.0f, 0.0f); // �}�[�J�[�̈ʒu��������
}
