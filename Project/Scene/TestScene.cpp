#include "TestScene.h"

void TestScene::Initialize()
{
	testAudioHandle_ = AudioManager::SoundLoadMp3("Resources/Sounds/testSound.mp3");
}

void TestScene::Update(GameManager* Scene)
{
	if (ImGui::Button("playAudio"))
	{
		AudioManager::AudioPlayMp3(testAudioHandle_);
	}

	if (Input::PushKeyPressed(DIK_B))
	{
		Scene->ChangeState(new GameScene);
		return;
	}

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
