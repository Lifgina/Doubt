#pragma once

#include "../HuEngine.h"
#include "../Class/View/BGMmanager.h"

class TitleScene : public HE::Scene
{
public:
	TitleScene();
	virtual ~TitleScene() { Terminate(); }

	void ResizeLayout() override;

	void Load() override;
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;

private:
	BGMmanager bgmManager_; // BGM�}�l�[�W���[

	HE::Sprite bg_; // �w�i��\������X�v���C�g
	bool isPressed_; // �{�^���������ꂽ���ǂ������Ǘ�����t���O

};
