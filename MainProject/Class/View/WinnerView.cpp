//
// WinnerView.cpp
//

#include "WinnerView.h"

using namespace HE;

void WinnerView::Load()
{
	for (int i = 0; i < 2; i++) {
		winnerFont_[i].params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
		winnerFont_[i].params.size = 36; // �t�H���g�T�C�Y��ݒ�
		winnerFont_[i].params.color = Color(0.0f, 0.0f, 0.0f); // �t�H���g�̐F��ݒ�
		RenderingPath->AddFont(&winnerFont_[i], 1000); // �����_�����O�p�X�ɒǉ�
	}
	winnerFont_[0].params.posX = 800.0f; // ���ҕ\���̈ʒu��ݒ�
	winnerFont_[0].params.posY = 360.0f; // ���ҕ\���̈ʒu��ݒ�
	winnerFont_[1].params.posX = 800.0f; // ���ҕ\���̈ʒu��ݒ�
	winnerFont_[1].params.posY = 400.0f; // ���ҕ\���̈ʒu��ݒ�

	
}


void WinnerView::ShowWinner(int winnerID)
{
	if (winnerID < 0 || winnerID >= 4) {
		return; // �����ȃv���C���[ID
	}
	winnerFont_[0].SetText("Winner: Player " + std::to_string(winnerID + 1)); // ���҂̃v���C���[ID��\��
	winnerFont_[1].SetText("Congratulations!"); // ���߂łƂ����b�Z�[�W��\��
	RenderingPath->AddFont(&winnerFont_[0], 1000); // �����_�����O�p�X�ɒǉ�
	RenderingPath->AddFont(&winnerFont_[1], 1000); // �����_�����O�p�X�ɒǉ�
	
	

}