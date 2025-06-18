//
// GameLog.cpp
//

#include "GameLog.h"

using namespace HE;

void GameLog::Load()
{
	for (int i = 0; i < 10; i++) {
		logText_[i].params.style = Font::AddFontStyle("Fonts/meiryob004.ttf");
		logText_[i].params.size = 20; // �t�H���g�T�C�Y��ݒ�
		logText_[i].params.color = Color(0.0f, 0.0f, 0.0f); // �t�H���g�̐F��ݒ�
		RenderingPath->AddFont(&logText_[i], 1000); // �����_�����O�p�X�ɒǉ�
		logText_[i].params.posX = 1000.0f; // ���O�̈ʒu��ݒ�
		logText_[i].params.posY = 275.0f + i * 20.0f; // ���O�̈ʒu��ݒ�
		logText_[i].SetText(L""); // ������Ԃł͋�̃e�L�X�g
	}
}


void GameLog::LogUpdate()
{
	// ���O�̍X�V����
	for (int i = 9; i > 0; --i) {
		logText_[i].SetText(logText_[i - 1].GetText()); // �O�̃��O�����ɂ��炷
	}

}

void GameLog::DiscardLog(int playerID, int discardCount)
{
	LogUpdate(); // ���O���X�V
	logText_[0].SetText(L"�v���C���[" + std::to_wstring(playerID + 1) + L"�̓J�[�h��" + std::to_wstring(discardCount) + L"���̂Ă��B");
}

void GameLog::DoubtLog(int playerID, bool isDoubt)
{
	LogUpdate(); // ���O���X�V
	if (isDoubt) {
		logText_[0].SetText(L"�v���C���[" + std::to_wstring(playerID + 1) + L"�̓_�E�g��錾�����I");
	}
	else {
		logText_[0].SetText(L"�v���C���[" + std::to_wstring(playerID + 1) + L"�̓X���[�����B");
	}
}

void GameLog::PenaltyLog(int playerID, bool doubtCorrect)
{
	LogUpdate(); // ���O���X�V
	if (doubtCorrect) {
		logText_[0].SetText(L"�v���C���[" + std::to_wstring(playerID + 1) + L"�̓_�E�g�ɐ����I�I");
	}
	else {
		logText_[0].SetText(L"�v���C���[" + std::to_wstring(playerID + 1) + L"�̓_�E�g�Ɏ��s�I�I");
	}
}