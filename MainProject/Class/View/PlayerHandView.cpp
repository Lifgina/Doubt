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
		playerHandSprites_[i].params.enableDrawRect(Rectf(
			0.0f, 0.0f, 100.0f, 150.0f
		));
		playerHandSprites_[i].params.siz = Math::Vector2(100.0f, 150.0f); // �J�[�h�̃T�C�Y��ݒ�
		playerHandSprites_[i].params.pos = Math::Vector2(-1000.0f, 0.0f); // �J�[�h�̈ʒu��������
	}
}

void PlayerHandView::UpdatePlayerHands(PlayerData playerdata_)
{
	// �v���C���[�̎�D���X�V
	int playerHands = playerdata_.GetPlayerHands(); // �v���C���[�̎�D�̖������擾
	for (int i = 0; i < playerHands; i++) {
		playerHandSprites_[i].params.pos = Math::Vector2(50.0f * i, RenderingPath->GetLogicalHeight()-200); // �J�[�h�̈ʒu��ݒ�
		int rank = playerdata_.GetCard(i).GetRank(); // �J�[�h�̃����N���擾
		int suit = playerdata_.GetCard(i).GetSuit(); // �J�[�h�̃X�[�g���擾
		playerHandSprites_[i].params.enableDrawRect(Rectf(
			100.0f*(rank-1), 150.0f*(suit), 100.0f, 150.0f
		)); // �J�[�h�̕`���`��ݒ�
		
	}

}

Math::Vector2 PlayerHandView::GetCardPosition(int index)
{
	// �w�肳�ꂽ�C���f�b�N�X�̃J�[�h�̈ʒu���擾
	if (index < 0 || index >= 52) {
		return Math::Vector2(-1000.0f, -1000.0f); // �����ȃC���f�b�N�X�̏ꍇ�͉�ʊO�̈ʒu��Ԃ�
	}
	return Math::Vector2(playerHandSprites_[index].params.pos.x, playerHandSprites_[index].params.pos.y); // �J�[�h�̈ʒu��Ԃ�
}