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
	bgmManager_.Load();

    Scene::Load();
}

// initialize a variables.
void TitleScene::Initialize()
{
	isPressed_ = false; // ������Ԃł̓L�[��������Ă��Ȃ�
	bg_.params.pos = Math::Vector2(0.0f, 0.0f); // �w�i�̈ʒu��ݒ�
	bg_.params.siz = Math::Vector2(1280.0f, 720.0f); // �w�i�̃T�C�Y��ݒ�
	RenderingPath->AddSprite(&bg_, 0); // �����_�����O�p�X�ɒǉ�
	bgmManager_.PlayBGMFromTop(0); // �^�C�g���V�[����BGM���Đ�
}

// releasing resources required for termination.
void TitleScene::Terminate()
{

}

// updates the scene.
void TitleScene::Update(float deltaTime)
{
	if (!isPressed_) {
		if (InputSystem.Keyboard.wasReleasedThisFrame.Enter) {
			SceneManager.SetNextScene(NextScene::MainScene, 2.0f, Color(0, 0, 0)); // Enter�L�[�������ꂽ��MainScene�ɑJ��
			isPressed_ = true; // 1�񂾂��������s�����߂Ƀt���O�𗧂Ă�
		}
	}



    Scene::Update(deltaTime);
}
