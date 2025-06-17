#pragma once

#include "../HuEngine.h"

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
	HE::Sprite bg_; // 背景を表示するスプライト
	bool isPressed_; // ボタンが押されたかどうかを管理するフラグ

};
