#pragma once
#include"Warp.h"

class WarpManager
{
public:
	WarpManager() {};
	~WarpManager() {};

	void Initialize();

	void Update();

	void DebugDraw();

#pragma region get
	vector<shared_ptr<Warp>>GetWarps() { return warps_; }
#pragma endregion


private:

	GameObjectManager* gameObjectManager_ = nullptr;

	vector<shared_ptr<Warp>>warps_ = {};


	uint32_t warpCount_ = 0;
};
