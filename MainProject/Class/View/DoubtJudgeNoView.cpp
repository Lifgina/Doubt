//
// DoubtJudgeNoView.cpp
//

#include "DoubtJudgeNoView.h"

using namespace HE;

void DoubtJudgeNoView::Load()
{
	sprite_ = Sprite("CardBack2.png");
	sprite_.params.siz = Math::Vector2(75.0f, 100.0f); // �X�v���C�g�̃T�C�Y��ݒ�
	font_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	font_.params.size = 36; // �t�H���g�T�C�Y��ݒ�
	font_.params.color = Color(0.0f, 0.0f, 0.0f); // �t�H���g�̐F��ݒ�
	guideFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	guideFont_.params.size = 24; // �K�C�h�t�H���g�̃T�C�Y��ݒ�
	guideFont_.params.color = Color(0.0f, 0.0f, 0.0f); // �K�C�h�t�H���g�̐F��ݒ�
	RenderingPath->AddSprite(&sprite_, 1000); // �����_�����O�p�X�ɒǉ�
	RenderingPath->AddFont(&font_, 1000); // �t�H���g�������_�����O�p�X�ɒǉ�
	RenderingPath->AddFont(&guideFont_, 1000); // �K�C�h�t�H���g�������_�����O�p�X�ɒǉ�
}

void DoubtJudgeNoView::Initialize()
{
	sprite_.params.pos = Math::Vector2(800.0f, 200.0f); // �X�v���C�g�̈ʒu��ݒ�
	font_.params.posX = 800.0f+75.0f/2-9.0f; // �t�H���g�̈ʒu��ݒ�
	font_.params.posY = 200.0f+30.0f; // �t�H���g�̈ʒu��ݒ�
	guideFont_.params.posX = 815.0f; // �t�H���g�̈ʒu��ݒ�
	guideFont_.params.posY = 300.0f; // �t�H���g�̈ʒu��ݒ�
	guideFont_.SetText(L"Next"); // �K�C�h�e�L�X�g��ݒ�	
}

void DoubtJudgeNoView::UpdateDoubtJudgeNo(int doubtJudgeNo)
{
	if (2<=doubtJudgeNo&&doubtJudgeNo <= 10)
	{
		font_.SetText(std::to_wstring(doubtJudgeNo)); // �_�E�g����̃J�[�h�ԍ���\��
	}
	else if(doubtJudgeNo == 11)
	{
		font_.SetText(L"J"); // �W���b�N�̏ꍇ
	}
	else if (doubtJudgeNo == 12)
	{
		font_.SetText(L"Q"); // �N�C�[���̏ꍇ
	}
	else if (doubtJudgeNo == 13)
	{
		font_.SetText(L"K"); // �L���O�̏ꍇ
	}
	else if (doubtJudgeNo == 1)
	{
		font_.SetText(L"A"); // �G�[�X�̏ꍇ
	}
	else
	{
		font_.SetText(L""); // �����Ȕԍ��̏ꍇ�͋�ɂ���
	}
	
}