#pragma once

#include "../../HuEngine.h"

class BGMmanager {
public:
	void Load(); // BGM�����[�h����֐�
	void PlayBGMFromTop(int BGMID);

private:
	int bgmCount_ = 2; // �Ǘ�����BGM�̐�
	HE::Sound bgm_[2]; // BGM���Ǘ�����I�u�W�F�N�g
	int currentBGMID_ = -1; // ���ݍĐ�����BGM��ID���Ǘ�����ϐ�
};