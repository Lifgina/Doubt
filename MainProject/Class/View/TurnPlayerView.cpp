//
// TurnPlayerView.cpp
//

#include "TurnPlayerView.h"

using namespace HE;

void TurnPlayerView::Load()
{
	turnPlayerFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
}

void TurnPlayerView::Initialize()
{
	turnPlayerFont_.params.size = 36; // �t�H���g�T�C�Y��ݒ�
	turnPlayerFont_.params.color = Color(0.0f, 0.0f, 0.0f); // �t�H���g�̐F��ݒ�
	turnPlayerFont_.params.posX = 1000.0f; 
	turnPlayerFont_.params.posY = 100.0f; 
	RenderingPath->AddFont(&turnPlayerFont_, 1000); // �����_�����O�p�X�ɒǉ�
}

void TurnPlayerView::UpdateTurnPlayerView(int turnPlayerID)
{
	turnPlayerFont_.SetText(L"�v���C���[" + std::to_wstring(turnPlayerID + 1)+L"�̔�"); // ���݂̎�Ԃ̃v���C���[ID��\��
}