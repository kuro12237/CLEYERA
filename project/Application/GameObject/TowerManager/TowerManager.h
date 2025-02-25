#pragma once
#include"Tower.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"

/// <summary>
/// 塔の管理クラス
/// </summary>
class TowerManager
{
public:
	TowerManager() {};
	~TowerManager() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region Set
	void SetP_Camera(const Math::Vector::Vector3& camera) { p_CameraPos_ = &camera; }
#pragma endregion

private:
	string name_ = "Tower";

	vector<shared_ptr<Tower>>towers_;
	const float towerOffset_ = 128.0f;

	const Math::Vector::Vector3* p_CameraPos_ = nullptr;
};