//
// WinnerView.cpp
//

#include "WinnerView.h"

using namespace HE;

void WinnerView::Load()
{
	
	winnerFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	winnerFont_.params.size = 72; // �t�H���g�T�C�Y��ݒ�
	winnerFont_.params.color = Color(0.0f, 0.0f, 0.0f); // �t�H���g�̐F��ݒ�
	RenderingPath->AddFont(&winnerFont_, 1200); // �����_�����O�p�X�ɒǉ�
	winnerFont_.params.posX = 400.0f; // ���ҕ\���̈ʒu��ݒ�
	winnerFont_.params.posY = 200.0f; // ���ҕ\���̈ʒu��ݒ�
	toTitleFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	toTitleFont_.params.size = 36; // �^�C�g���֖߂�t�H���g�̃T�C�Y��ݒ�
	toTitleFont_.params.color = Color(0.0f, 0.0f, 0.0f); // �^�C�g���֖߂�t�H���g�̐F��ݒ�
	toTitleFont_.params.posX = 500.0f; // �^�C�g���֖߂�t�H���g�̈ʒu��ݒ�
	toTitleFont_.params.posY = 400.0f; // �^�C�g���֖߂�t�H���g�̈ʒu��ݒ�
	RenderingPath->AddFont(&toTitleFont_, 1200); // �^�C�g���֖߂�t�H���g�������_�����O�p�X�ɒǉ�
	winnerBack_ = Sprite("WinnerBack.png"); // ���ҕ\���̔w�i�X�v���C�g��ǂݍ���
	winnerBack_.params.siz = Math::Vector2(800.0f, 450.0f); // �w�i�̃T�C�Y��ݒ�
	winnerBack_.params.pos = Math::Vector2(240.0f, 360.0-225.0f); // �w�i�̈ʒu��ݒ�
	winnerBack_.SetHidden(true); // ������Ԃł͔w�i���\���ɂ���
	RenderingPath->AddSprite(&winnerBack_, 1100); // �w�i�X�v���C�g�������_�����O�p�X�ɒǉ�

	
}


void WinnerView::ShowWinner(int winnerID)
{
	if (winnerID < 0 || winnerID >= 4) {
		return; // �����ȃv���C���[ID
	}
	winnerFont_.SetText(L"Winner: Player " + std::to_wstring(winnerID + 1)); // ���҂̃v���C���[ID��\��
	toTitleFont_.SetText(L"����{�^���Ń^�C�g���֖߂�"); // �^�C�g���֖߂郁�b�Z�[�W��\��
	winnerBack_.SetHidden(false); // �w�i��\��
	
	

}