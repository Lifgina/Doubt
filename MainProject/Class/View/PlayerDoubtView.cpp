//
// PlayerDoubtView.cpp
//

#include "PlayerDoubtView.h"

using namespace HE;

void PlayerDoubtView::Load()
{
	for (int i = 0; i < 3; i++) {
		doubtText_[i].params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
		doubtText_[i].params.size = 36; // �t�H���g�T�C�Y��ݒ�
		doubtText_[i].params.color = Color(0.0f, 0.0f, 0.0f); // �t�H���g�̐F��ݒ�
		RenderingPath->AddFont(&doubtText_[i], 1000); // �����_�����O�p�X�ɒǉ�
	}
	doubtText_[0].params.posX = 800.0f; // �_�E�g���j���[�̈ʒu��ݒ�
	doubtText_[0].params.posY = 360.0f; // �_�E�g���j���[�̈ʒu��ݒ�
	doubtText_[1].params.posX = 800.0f; // �_�E�g���j���[�̈ʒu��ݒ�
	doubtText_[1].params.posY = 400.0f; // �_�E�g���j���[�̈ʒu��ݒ�
	doubtText_[2].params.posX = 800.0f; // �_�E�g���j���[�̈ʒu��ݒ�
	doubtText_[2].params.posY = 440.0f; // �_�E�g���j���[�̈ʒu��ݒ�
	
}

void PlayerDoubtView::ShowDoubtMenu()
{

	doubtText_[0].SetText("�_�E�g����?"); // �_�E�g���j���[�̈ʒu��ݒ�
	doubtText_[1].SetText("��:�_�E�g");
	doubtText_[2].SetText("��:�X���[");
}

void PlayerDoubtView::HideDoubtMenu()
{
	for (int i = 0; i < 3; i++) {
		doubtText_[i].SetText(""); // �_�E�g���j���[�̃e�L�X�g����ɂ���
	}
}