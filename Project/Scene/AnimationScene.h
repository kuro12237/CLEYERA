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
#include<vector>
class AnimationScene :public IScene
{
public:
	AnimationScene() {};
	~AnimationScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void PostProcessDraw()override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;

private:
	CameraData camera_{};
	unique_ptr<DebugCamera>debugCamera_ = nullptr;

	unique_ptr<PostEffect>postEffect_ = nullptr;

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	Game3dObjectDesc gameObjetcDesc{};

	WorldTransform worldTransform_{};

	PointLight_param pointLight_ = {};

	float animationFlame_ = 0.0f;
	uint32_t modelHandle_ = 0;

	unique_ptr<Game3dObject>testBox_ = nullptr;
	Game3dObjectDesc testBoxDesc_ = {};
	WorldTransform testBoxWorldTransform_ = {};
	uint32_t debugModelHandle_ = 0;
};