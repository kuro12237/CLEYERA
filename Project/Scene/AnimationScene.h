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
#include"DebugTool/DebugSkeleton/DebugSkeleton.h"
#include"Model/primitive/Line.h"

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
	uint32_t modelHumanHandle_ = 0;

	array<unique_ptr<Game3dObject>,128>testBox_ = {};
	Game3dObjectDesc testBoxDesc_ = {};
	array<WorldTransform,128> testBoxWorldTransform_ = {};
	uint32_t debugModelHandle_ = 0;

	SAnimation::Animation animationData_;

	string fileName_ = "Walk";

	unique_ptr<DebugSkeleton>debugSkeleton_ = nullptr;
	unique_ptr<LineModel>line_ = nullptr;
	Math::Matrix::Matrix4x4 endMat_;
	Math::Vector::Vector3 translate_{};
};
