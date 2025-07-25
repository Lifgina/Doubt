//
// BGMmanager.cpp
//

#include "BGMmanager.h"

using namespace HE;

void BGMmanager::Load()
{
	bgm_[0] = Sound("TitleBGM.wav",Sound::LoopCount::BGM);
	bgm_[1] = Sound("MainBGM.wav", Sound::LoopCount::BGM);
	bgm_[2] = Sound("WinBGM.wav", Sound::LoopCount::SE);

}

void BGMmanager::PlayBGMFromTop(int BGMID)
{
	if (BGMID < 0 || BGMID >= bgmCount_) {
		return; // 無効なBGMIDの場合は何もしない
	}
	if (currentBGMID_ != -1) {
		bgm_[currentBGMID_].Stop(); // 前のBGMを停止
	}
	
	bgm_[BGMID].PlayFromTop(); // 指定されたBGMを再生
}