//
// TitleScene.cpp
//

#include "TitleScene.h"

using namespace HE;

// initialize member variables.
TitleScene::TitleScene()
{

}

// rearrange UI to fit the size.
void TitleScene::ResizeLayout()
{
    Scene::ResizeLayout();



}

// load resources.
void TitleScene::Load()
{
	bg_ = Sprite("Title.png");


    Scene::Load();
}

// initialize a variables.
void TitleScene::Initialize()
{
	bg_.params.pos = Math::Vector2(0.0f, 0.0f); // �w�i�̈ʒu��ݒ�
	bg_.params.siz = Math::Vector2(1280.0f, 720.0f); // �w�i�̃T�C�Y��ݒ�
	RenderingPath->AddSprite(&bg_, 0); // �����_�����O�p�X�ɒǉ�
}

// releasing resources required for termination.
void TitleScene::Terminate()
{

}

// updates the scene.
void TitleScene::Update(float deltaTime)
{
	if (InputSystem.Keyboard.wasReleasedThisFrame.Enter) {
		SceneManager.SetNextScene(NextScene::MainScene,2.0f,Color(0,0,0)); // Enter�L�[�������ꂽ��MainScene�ɑJ��
	}


    Scene::Update(deltaTime);
}
