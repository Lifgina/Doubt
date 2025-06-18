//
// ClassTemplete.cpp
//

#include "CheckerView.h"

using namespace HE;

void CheckerView::Load()
{
	checkerSprite_ = Sprite("Checker.png");
	RenderingPath->AddSprite(&checkerSprite_, 0); // �����_�����O�p�X�ɒǉ�
	checkerSprite_.params.siz = Math::Vector2(25.0f, 25.0f); // �`�F�b�J�[�̃T�C�Y��ݒ�
	checkerSprite_.params.pos = Math::Vector2(-1000.0f, 0.0f); // �����ʒu��ݒ�
}


void CheckerView::UpdateChecker(Math::Vector2 cardpos)
{
	checkerSprite_.params.pos = Math::Vector2(cardpos.x + 75.0f / 8, cardpos.y+5.0f ); // �`�F�b�J�[�̈ʒu���X�V
}

void CheckerView::CheckerDelete()
{
	checkerSprite_.params.pos = Math::Vector2(-1000.0f, 0.0f); // �`�F�b�J�[�̈ʒu��������
}