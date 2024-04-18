#include "TestScene.h"

void TestScene::Initialize()
{
	AudioManager::GetInstance()->SoundLoadMp3("Resources/Sounds/testSound.mp3");
	AudioManager::GetInstance()->SoundLoadWave("Resources/Sounds/hit.wav");
}

void TestScene::Update(GameManager* Scene)
{
	if (ImGui::Button("playAudio"))
	{
		AudioManager::GetInstance()->AudioPlayMp3("Resources/Sounds/testSound.mp3");
	}
	if (ImGui::Button("playhitAudio"))
	{
		AudioManager::GetInstance()->AudioPlayWave("Resources/Sounds/hit.wav");
	}
	Scene;
	/*if (Input::PushKeyPressed(DIK_B))
	{
		Scene->ChangeState(new GameScene);
		return;
	}*/

}

void TestScene::PostProcessDraw()
{
}

void TestScene::Back2dSpriteDraw()
{
}

void TestScene::Object3dDraw()
{
}

void TestScene::Flont2dSpriteDraw()
{
}
