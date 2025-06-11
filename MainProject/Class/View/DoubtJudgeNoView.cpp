//
// DoubtJudgeNoView.cpp
//

#include "DoubtJudgeNoView.h"

using namespace HE;

void DoubtJudgeNoView::Load()
{
	sprite_ = Sprite("");
	sprite_.params.siz = Math::Vector2(75.0f, 100.0f); // �X�v���C�g�̃T�C�Y��ݒ�
	font_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	font_.params.size = 36; // �t�H���g�T�C�Y��ݒ�
	font_.params.color = Color(0.0f, 0.0f, 0.0f); // �t�H���g�̐F��ݒ�
	RenderingPath->AddSprite(&sprite_, 1000); // �����_�����O�p�X�ɒǉ�
	RenderingPath->AddFont(&font_, 1000); // �t�H���g�������_�����O�p�X�ɒǉ�
}

void DoubtJudgeNoView::Initialize()
{
	sprite_.params.pos = Math::Vector2(800.0f, 200.0f); // �X�v���C�g�̈ʒu��ݒ�
	font_.params.posX = 800.0f+75.0f/2; // �t�H���g�̈ʒu��ݒ�
	font_.params.posY = 200.0f+50.0f; // �t�H���g�̈ʒu��ݒ�
}

void DoubtJudgeNoView::UpdateDoubtJudgeNo(int doubtJudgeNo)
{
	font_.SetText(std::to_string(doubtJudgeNo)); // �_�E�g����̃J�[�h�ԍ���\��
}