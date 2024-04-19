#pragma once
#include"GameManager.h"
#include"GameObject/WoodBlockManager/WoodBlockManager.h"
#include"GameObject/Sun/Sun.h"


class GameScene:public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void PostProcessDraw()override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;


private:

	const string sceneName = "GameScene";

	CameraData cameraData = {};

	unique_ptr<PostEffect>postEffect_ = nullptr;

	unique_ptr<Sun>sun_ = nullptr;

	unique_ptr<WoodBlockManager>woodBlockManager_ = nullptr;


};


