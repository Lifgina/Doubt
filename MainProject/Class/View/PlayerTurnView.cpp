//
// PlayerTurnView.cpp
//

#include "PlayerTurnView.h"

using namespace HE;

void PlayerTurnView::Load()
{
	playerTurnFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	playerTurnFont_.params.size = 36; // �t�H���g�T�C�Y��ݒ�
	playerTurnFont_.params.color = Color(0.0f, 0.0f, 0.0f); // �t�H���g�̐F��ݒ�
	RenderingPath->AddFont(&playerTurnFont_, 1000); // �����_�����O�p�X�ɒǉ�
}

void PlayerTurnView::Initialize()
{
	playerTurnFont_.params.posX = 430.0f; // �v���C���[�̃^�[���̈ē��̈ʒu��ݒ�
	playerTurnFont_.params.posY = 400.0f; // �v���C���[�̃^�[���̈ē��̈ʒu��ݒ�
}

void PlayerTurnView::ShowPlayerTurnUI()
{
	playerTurnFont_.SetText(L"�J�[�h��4���܂őI��ŏo�����I"); // �v���C���[�̃^�[���̈ē���\��
}
void PlayerTurnView::HidePlayerTurnUI()
{
	playerTurnFont_.SetText(L""); // �v���C���[�̃^�[���̈ē����\���ɂ���
}