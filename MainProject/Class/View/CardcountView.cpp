//
// CardcountView.cpp
//

#include "CardcountView.h"

using namespace HE;

void CardcountView::Load()
{
	cardBackSprite_ = Sprite("CardBack2.png");
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

void CardcountView::SetPlayerID(int playerID)
{
	playerIDFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	playerIDFont_.params.size = 24; // �t�H���g�T�C�Y��ݒ�
	playerIDFont_.params.color = Color(0.0f, 0.0f, 0.0f); // �t�H���g�̐F��ݒ�
	playerIDFont_.params.posX = cardBackSprite_.params.pos.x-5.0f ; // �v���C���[ID�̈ʒu��ݒ�
	playerIDFont_.params.posY = cardBackSprite_.params.pos.y + 100.0f; // �v���C���[ID�̈ʒu��ݒ�
	playerIDFont_.SetText(L"�v���C���[" + std::to_wstring(playerID + 1)); // �v���C���[ID��\��
	RenderingPath->AddFont(&playerIDFont_, 1000); // �����_�����O�p�X�ɒǉ�
}

void CardcountView::UpdateCardcount(int playerCardcount)
{
	cardCountsFont_.SetText(std::to_string(playerCardcount));
}