#pragma once
#include"GameManager.h"
#include"IScene.h"
#include"TestLevelDataScene.h"

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


	CameraData camera_{};

	unique_ptr<PostEffect>postEffect_ = nullptr;

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform wT_ = {};
	Game3dObjectDesc desc_;


	PointLight_param light_{};

	uint32_t testAudioHandle_ = 0;
	uint32_t testAudioWaveHandle_ = 0;
};