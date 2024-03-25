#pragma once
#include"GameManager.h"
#include"IScene.h"
#include"GameScene.h"

class TestScene :public IScene
{
public:
	TestScene() {};
	~TestScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void PostProcessDraw()override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;
private:

	
};