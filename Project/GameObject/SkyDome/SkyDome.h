#pragma once
#include"Game3dObject.h"

class SkyDome
{
public:
	SkyDome() {};
	~SkyDome() {};

	void Initialize();

	void Update();

	void Draw(const CameraData &camera);

	void ImGuiUpdate();

private:

	uint32_t modelHandle_ = 0;
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	Game3dObjectDesc gameObjectDesc_ = {};
	WorldTransform worldTransform_ = {};

};