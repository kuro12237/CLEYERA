#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"PostEffect/PostEffect.h"
#include"Game3dObject.h"
#include"TestScene.h"
#include"DebugTool/DebugCamera/DebugCamera.h"
#include"PostEffect/DeferrdShading/DeferredShading.h"
#include"Animation/AnimationManager.h"

class CGScene :public IScene
{
public:
	CGScene() {};
	~CGScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void PostProcessDraw()override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;

private:

	void Move();

	void TestAnimation();

	float animationTimer_ = 0.0f;


	CameraData viewProjection_ = {};
	CameraData testViewProjection_ = {};

	unique_ptr<PostEffect>postEffect_ = nullptr;

	Math::Vector::Vector2 postEffectuvScale = { 1,1 };
	float postEffectGrayFactor_ = 0.0f;
	float postEffectInvertFactor_ = 0.0f;
	float postEffectBringhtnessFactor_ = 0.0f;
	float postEffectAverageBlurIntensity_ = 0.0f;
	float postEffectContrastFactor_ = 0.0f;
	float postEffectHueFactor_ = 0.0f;

	SelectPostEffect selectPostEffect_ = GRAYSCALE;

	unique_ptr<PostEffect>postEffectTest_ = nullptr;
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	Game3dObjectDesc ObjectDesc_ = {};

	WorldTransform worldTransform_ = {};

	unique_ptr<Game3dObject>testSkyDomeGameObject_ = nullptr;
	Game3dObjectDesc SkyObjectDesc_ =  {};

	WorldTransform TestSkyDomeWorldTreanform_ = {};
	unique_ptr<Game3dObject>testGroundGameObject_ = nullptr;
	
	WorldTransform testGroundWorldTransform_ = {};
	Game3dObjectDesc GroundObjectDesc_ = {};

	PointLight_param light_ = {};
	PointLight_param testLight = {};
	bool UseTestRedLight_ = false;
	ModelShaderSelect modelPipline_ = PHONG_MODEL;

	uint32_t normalMonkeyHandle_ = 0;
	uint32_t smoothMonkeyHandle_ = 0;

	// 散乱係数
	float scatterCoefficient_ = 0.5f;
	// 吸収係数 
	float absorptionCoefficient_ = 0.5f;
	//光の伝播距離
	float scatterDistance_ = 0.5f;

	bool SmoothMoneyUseFlag_ = false;

	unique_ptr<DebugCamera>debugCamera_ = nullptr;

	unique_ptr<DefferredShading>defferedShading = nullptr;



};