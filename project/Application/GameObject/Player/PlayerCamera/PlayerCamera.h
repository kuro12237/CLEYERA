#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"

/// <summary>
/// プレイヤーカメラ
/// </summary>
class PlayerCamera:public IObjectData
{
public:
	PlayerCamera() {};
	~PlayerCamera() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region Set

	void SetTargetName(string target) { targetName_ = target; }

#pragma endregion

#pragma region Get

#pragma endregion

private:

	void Shake();


	Math::Vector::Vector3 CalcOffset(const Engine::Transform::WorldTransform& w ,const Math::Vector::Vector3 v)const;

	GameObjectManager* gameObjInstance_ = nullptr;
	string targetName_ = "";
	const Engine::Transform::WorldTransform* target_ = nullptr;

	Math::Vector::Vector3 interTarget_{};
	float distructionAngleY_ = 0.0f;
	float lerp_t = 0.0f;

	Math::Vector::Vector2 cameraShakeRadious_ = { -1.0f,1.0f };
	bool isShake_ = false;
};

