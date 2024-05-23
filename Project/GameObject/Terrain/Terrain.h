#pragma once
#include"Game3dObject.h"

class Terrain
{
public:
	Terrain() {};
	~Terrain() {};

	void Initialize();

	void Update();

	void Draw();

	void ImGuiUpdate();

private:

	uint32_t modelHandle_ = 0;
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};

	Game3dObjectDesc objectDesc_ = {};
};