#pragma once
#include"GameFileLoader/RailLoader/RailLoader.h"
#include"Utility/SplineMotion/SplineMotion.h"

/// <summary>
/// RailDataのルートのモデル表示
/// </summary>
class WarpRuate
{
public:
	WarpRuate() {};
	~WarpRuate() {};

	void Initialize(const string& fileName);

	void ImGuiUpdate();

	void Update();

	void Draw();

	RailData GetRailData() { return railData_; }

private:

	RailData railData_ = {};

	unique_ptr<Engine::Objects::Game3dObject>gameObject_ = nullptr;
	Engine::Transform::WorldTransform worldTransform_ = {};

	float kFlame_ = 60.0f;

	unique_ptr<SplineMotion>splineMotion_ = nullptr;

	bool isStart_ = false;
};
