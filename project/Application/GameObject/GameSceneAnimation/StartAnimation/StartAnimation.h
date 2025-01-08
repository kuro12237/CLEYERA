#pragma once
#include"GameFileLoader/RailLoader/RailLoader.h"
#include"Utility/SplineMotion/SplineMotion.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"StartCount/StartCount.h"
#include"Utility/convert/convert.h"
#include"../IGameSceneAnimation.h"

#include"state/IStartAnimationState.h"
#include"state/StartAnimationStateCamera.h"

/// <summary>
/// スタート演出のモーション
/// </summary>
class StartAnimation:public IGameSceneAnimation
{
public:
	StartAnimation() {};
	~StartAnimation() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(uint32_t stageNum);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// pointを描画
	/// </summary>
	void DebugLine();

	/// <summary>
	/// 2dスプライト表示
	/// </summary>
	void Draw2d();

#pragma region Set
	void SetIsCountStart(const bool& flag) { isCountStart_ = flag; }
#pragma endregion

#pragma region Get
	bool GetIsGameStartFlag() { return isGameStart_; }
	bool GetIsStartFlag() { return isCountStart_; }
#pragma endregion

private:

	/// <summary>
	/// フレームを更新
	/// </summary>
	void FlameUpdate();

	void EndVinatteAnimation();

	void SkipAnimation();

	bool isSkip_ = false;
	bool isGameStart_ = false;
	bool isCountStart_ = false;
	bool isStartCount_ = false;
	bool isCameraMotion_ = false;

	unique_ptr<StartCount>startCount_ = nullptr;

	float vinatteFlame_ = 0.0f;
	float flameCount_ = 0.0f;

	bool isFlameCount_ = false;
	bool isPrevFlameCount_ = false;


	float vinatteScaleMax_ = 1.0f;

	unique_ptr<IStartAnimation>state_ = nullptr;

	friend class StartAnimationStateCamera;
};
