#pragma once
#include"Tower.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"

/// <summary>
/// ���̊Ǘ��N���X
/// </summary>
class TowerManager
{
public:
	TowerManager() {};
	~TowerManager() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
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