//
// BGMmanager.cpp
//

#include "BGMmanager.h"

using namespace HE;

void BGMmanager::Load()
{
	bgm_[0] = Sound("TitleBGM.wav",Sound::LoopCount::BGM);
	bgm_[1] = Sound("MainBGM.wav", Sound::LoopCount::BGM);
}

void BGMmanager::PlayBGMFromTop(int BGMID)
{
	if (BGMID < 0 || BGMID >= bgmCount_) {
		return; // ������BGMID�̏ꍇ�͉������Ȃ�
	}
	if (currentBGMID_ != -1) {
		bgm_[currentBGMID_].Stop(); // �O��BGM���~
	}
	
	bgm_[BGMID].PlayFromTop(); // �w�肳�ꂽBGM���Đ�
}