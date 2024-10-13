#pragma once
#include"Tower.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"

class TowerManager
{
public:
	TowerManager() {};
	~TowerManager() {};

	void Initialize();

	void Update();

	vector<shared_ptr<Tower>>GetBlocks() { return towers_; }
	
	void SetP_Camera(const Math::Vector::Vector3& camera) { p_CameraPos_ = &camera; }

private:
	string name_ = "Tower";

	vector<shared_ptr<Tower>>towers_;
	const float towerOffset_ = 128.0f;

	const Math::Vector::Vector3* p_CameraPos_ = nullptr;
};