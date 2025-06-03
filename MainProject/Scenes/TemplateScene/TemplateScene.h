#pragma once

#include "../HuEngine.h"

class TemplateScene : public HE::Scene
{
public:
	TemplateScene();
	virtual ~TemplateScene() { Terminate(); }

	void ResizeLayout() override;

	void Load() override;
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;

private:



};
