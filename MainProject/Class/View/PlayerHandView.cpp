//
// PlayerHandView.cpp
//

#include "PlayerHandView.h"

using namespace HE;

void PlayerHandView::Load()
{
	for (int i = 0; i < 52; i++) {
		playerHandSprites_[i]= Sprite("CardsFront.png");
		RenderingPath->AddSprite(&playerHandSprites_[i], 0); // �����_�����O�p�X�ɒǉ�
	}
}

void PlayerHandView::Initialize()
{
	for (int i = 0; i < 52; i++) {
		playerHandSprites_[i].params.siz = Math::Vector2(100.0f, 150.0f); // �J�[�h�̃T�C�Y��ݒ�
		playerHandSprites_[i].params.enableDrawRect(Rectf(
			256.0f, 0.0f, 64.0f, 64.0f
		));
		playerHandSprites_[i].params.pos = Math::Vector2(0.0f + 0.1 * i, 0.0f + 0.1 * i); // �J�[�h�̈ʒu��������
	
	}
}

void PlayerHandView::Update()
{

}