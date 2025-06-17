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
	bg_.params.pos = Math::Vector2(0.0f, 0.0f); // 背景の位置を設定
	bg_.params.siz = Math::Vector2(1280.0f, 720.0f); // 背景のサイズを設定
	RenderingPath->AddSprite(&bg_, 0); // レンダリングパスに追加
}

// releasing resources required for termination.
void TitleScene::Terminate()
{

}

// updates the scene.
void TitleScene::Update(float deltaTime)
{
	if (InputSystem.Keyboard.wasReleasedThisFrame.Enter) {
		SceneManager.SetNextScene(NextScene::MainScene,2.0f,Color(0,0,0)); // Enterキーが押されたらMainSceneに遷移
	}


    Scene::Update(deltaTime);
}
