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

}

void DiscardView::ResetDiscard()
{
	for (int i = 0; i < 52; i++) {
		cardSprite_[i].SetHidden(true); // �S�ẴJ�[�h���\���ɂ���
		cardSprite_[i].params.pos = Math::Vector2(640.0f, 200.0f); // �J�[�h�̈ʒu��������
	}
	discardCount_ = 0; // �̂ĎD�̖��������Z�b�g
}