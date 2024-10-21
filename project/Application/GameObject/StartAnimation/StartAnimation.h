#pragma once
#include"GameFileLoader/RailLoader/RailLoader.h"
#include"Utility/SplineMotion/SplineMotion.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"StartCount/StartCount.h"
#include"Utility/convert/convert.h"
#include"StartAnimationParticle/StartAnimation2dParticle.h"

class StartAnimation
{
public:
	StartAnimation() {};
	~StartAnimation() {};

	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Initialize();

	/// <summary>
	/// çXêV
	/// </summary>
	void Update();

	/// <summary>
	/// pointÇï`âÊ
	/// </summary>
	void DebugLine();

	void Draw2d();

	void SetIsCountStart(const bool& flag) { isCountStart_ = flag; }


	bool GetIsGameStartFlag() { return isGameStart_; }
	bool GetIsStartFlag() { return isCountStart_; }

private:

	GameObjectManager* gameObjectManager_ = nullptr;
	PostEffect* postEffect_ = nullptr;

	vector<unique_ptr<SplineMotion>>splineMotions_;
	uint32_t splineMotionsMax_ = 2;
	vector<RailData>railData_;

	unique_ptr<StartAnimation2dParticle>particle_ = nullptr;

	bool isGameStart_ = false;
	bool isCountStart_ = false;
	bool isStartCount_ = false;
	bool isCameraMotion_ = false;

	unique_ptr<StartCount>startCount_ = nullptr;

	string selectCameraName_ = "StartCamera";

	float vinatteFlame_ = 0.0f;
	float flameCount_ = 0.0f;
	bool isFlameCount_ = false;
	bool isPrevFlameCount_ = false;

	float vinatteScaleMax_ = 640.0f;
};
