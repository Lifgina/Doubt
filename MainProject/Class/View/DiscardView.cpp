//
// DiscardView.cpp
//

#include "DiscardView.h"
#include <numbers>

using namespace HE;

void DiscardView::Load()
{
	for (int i = 0; i < 52; i++) {
		cardSprite_[i] = Sprite("CardBack.png");
		cardSprite_[i].params.siz = Math::Vector2(100.0f, 150.0f); // �J�[�h�̃T�C�Y��ݒ�
		RenderingPath->AddSprite(&cardSprite_[i], 1000); // �����_�����O�p�X�ɒǉ�
	}
	discardFont_.params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
	discardFont_.params.size = 36; // �t�H���g�T�C�Y��ݒ�
	discardFont_.params.color = Color(0.0f, 0.0f, 0.0f); // �t�H���g�̐F��ݒ�
	RenderingPath->AddFont(&discardFont_, 1000); // �����_�����O�p�X�ɒǉ�
}

void DiscardView::Initialize(int playerCount, int myPlayerID)
{
	myPlayerID_ = myPlayerID; // �����̃v���C���[ID��ݒ�
	playerCount_ = playerCount; // �v���C���[�̐l����ݒ�
	for (int i = 0; i < 52; i++) {
		cardSprite_[i].params.pos = Math::Vector2(640.0f, 300.0f); // �J�[�h�̈ʒu��ݒ�
		cardSprite_[i].params.pivot = Math::Vector2(0.5, 0.5); // �J�[�h�̃s�{�b�g�𒆉��ɐݒ�
		cardSprite_[i].SetHidden(true); // ������Ԃł̓J�[�h���\���ɂ���
	}
	discardFont_.params.posX = 350.0f; // �̂ĎD�̖����\���̈ʒu��ݒ�
	discardFont_.params.posY = 200.0f; // �̂ĎD�̖����\���̈ʒu��ݒ�
	discardFont_.SetText(L"�̂ĎD:0��"); // �̂ĎD�̖����\�������Z�b�g
}

void DiscardView::Discard(int playerID, int currentDiscardCount)
{
	for (int i = 0; i < currentDiscardCount; i++)
	{
		discardCount_ += 1;
		cardSprite_[discardCount_].SetHidden(false);
		cardSprite_[discardCount_].params.pos.x = 640.0f - 20.0f*(currentDiscardCount-1) + 40.0f * (i); // �J�[�h�̈ʒu��ݒ�
		cardSprite_[discardCount_].params.rotation = 2 * std::numbers::pi / playerCount_ * (playerID + playerCount_ - myPlayerID_ % playerCount_); // ��]�p�x��ݒ�
	}
	discardFont_.SetText(L"�̂ĎD:"+std::to_wstring(discardCount_)+L"��"); // �̂ĎD�̖�����\��
}

void DiscardView::ResetDiscard()
{
	for (int i = 0; i < 52; i++) {
		cardSprite_[i].SetHidden(true); // �S�ẴJ�[�h���\���ɂ���
		cardSprite_[i].params.pos = Math::Vector2(640.0f, 300.0f); // �J�[�h�̈ʒu��������
	}
	discardCount_ = 0; // �̂ĎD�̖��������Z�b�g
	discardFont_.SetText(L"�̂ĎD:0��"); // �̂ĎD�̖����\�������Z�b�g
}