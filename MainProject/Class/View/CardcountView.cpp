//
// CardcountView.cpp
//

#include "CardcountView.h"

using namespace HE;

void CardcountView::Load()
{
	cardBackSprite_ = Sprite("");
	RenderingPath->AddSprite(&cardBackSprite_, 0); // �����_�����O�p�X�ɒǉ�
	cardCountsFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	cardCountsFont_.params.size = 36; // �t�H���g�T�C�Y��ݒ�
	cardCountsFont_.params.color = Color(0.0f, 0.0f, 0.0f); // �t�H���g�̐F��ݒ�
	RenderingPath->AddFont(&cardCountsFont_, 1000); // �����_�����O�p�X�ɒǉ�
}

void CardcountView::Initialize(Math::Vector2 position)
{
	cardBackSprite_.params.pos = position; // �J�[�h�̗��ʂ̈ʒu��ݒ�
	cardBackSprite_.params.siz = Math::Vector2(75.0f, 100.0f); // �J�[�h�̃T�C�Y��ݒ�
	cardCountsFont_.params.posX = position.x + 75.0f/2-18; // �J�[�h�̖����\���̈ʒu��ݒ�
	cardCountsFont_.params.posY = position.y + 100.0f/2-18; // �J�[�h�̖����\���̈ʒu��ݒ�

}

void CardcountView::UpdateCardcount(int playerCardcount)
{
	cardCountsFont_.SetText(std::to_string(playerCardcount));
}