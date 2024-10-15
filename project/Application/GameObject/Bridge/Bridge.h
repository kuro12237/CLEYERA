#pragma once
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"

/// <summary>
/// ��
/// </summary>
class Bridge :public IObjectData
{
public:
	Bridge() {};
	~Bridge() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
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
	/// �A�j���[�V�����֐�
	/// </summary>
	float EaseOutBounce(float x);
	/// <summary>
	/// Vec3�A�j���[�V�����֐�
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
