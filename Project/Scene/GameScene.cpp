#include "GameScene.h"

void GameScene::Initialize()
{
	cameraData.Initialize();

	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize(sceneName);

	sun_ = make_unique<Sun>();
	sun_->Initialize();

	woodBlockManager_ = make_unique<WoodBlockManager>();
	woodBlockManager_->Initialize();


}

void GameScene::Update(GameManager* Scene)
{
	Scene;



	woodBlockManager_->Update();
	
	sun_->Update();
	
	cameraData.UpdateMatrix();

	postEffect_->Update();
}

void GameScene::PostProcessDraw()
{
	postEffect_->PreDraw();


	woodBlockManager_->Draw(cameraData);

	postEffect_->PostDraw();

}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
}

void GameScene::Flont2dSpriteDraw()
{
	postEffect_->Draw(cameraData);
}
