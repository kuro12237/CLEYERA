#pragma once
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"

/// <summary>
/// 橋
/// </summary>
class Bridge :public ObjectComponent
{
public:
	Bridge() {};
	~Bridge() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region Set
	void SetTargetPos(Math::Vector::Vector3 targetPos) { targetPos_ = targetPos; }
	void SetIsStartAnimation(bool f) { isStartAnimation_ = f; }
#pragma endregion

#pragma region Get
	bool GetIsStartAnimation() { return isStartAnimation_; }
#pragma endregion

private:

	/// <summary>
	/// アニメーション関数
	/// </summary>
	float EaseOutBounce(float x);
	/// <summary>
	/// Vec3アニメーション関数
	/// </summary>
	Math::Vector::Vector3  EaseOutBounceLerp(const Math::Vector::Vector3& startPos, const Math::Vector::Vector3& endPos, float t);

	GameObjectManager* gameObjectManager_ = nullptr;
	Math::Vector::Vector3 targetPos_ = {};
	Math::Vector::Vector3 startPos_ = {};
	float animationFlame_ = 0.0f;
	float animationFlameSpeed_ = 0.01f;
	float animationFlameMax_ = 1.0f;
	bool isStartAnimation_ = false;
	bool isAnimation_ = false;
};
