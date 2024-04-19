#pragma once
#include"Game3dObject.h"

class Terrain
{
public:
	Terrain() {};
	~Terrain() {};

	void Initialize();

	void Update();

	void Draw(const CameraData& camera);

	void ImGuiUpdate();

private:

	uint32_t modelHandle_ = 0;
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};

};