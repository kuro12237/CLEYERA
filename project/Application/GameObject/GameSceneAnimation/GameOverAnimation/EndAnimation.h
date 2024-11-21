#pragma once
#include"GameFileLoader/RailLoader/RailLoader.h"
#include"Utility/SplineMotion/SplineMotion.h"
#include"Utility/ObjectManager/GameObjectManager.h"

#include"Utility/convert/convert.h"
#include"PostEffect/PostEffect.h"

#include"../IGameSceneAnimation.h"

/// <summary>
/// ゲーム終了時のアニメーション
/// </summary>
class EndAnimation
{
public:
	EndAnimation() {};
	~EndAnimation() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 2dスプライト表示
	/// </summary>
	void Draw2d();

#pragma region Set
	void SetIsCountStart(const bool& flag) { isCountStart_ = flag; }
#pragma endregion

#pragma region Get
	bool GetIsStartFlag() { return isCountStart_; }
	bool GetCompleteFlag() { return isComplete_; }
#pragma endregion

private:

	bool isGameEnd_ = false;;
	bool isCountStart_ = false;


	GameObjectManager* gameObjectManager_ = nullptr;
	Engine::PostEffect* postEffect_ = nullptr;

	bool isComplete_ = false;

};
