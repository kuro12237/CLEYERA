#pragma once
#include"Warp.h"
#include"GameObject/ObjectInterface/ManagerComponent.h"

/// <summary>
/// ワープ管理クラス
/// </summary>
class WarpManager :public ManagerComponent
{
public:
	WarpManager() {};
	~WarpManager() {};

	void Initialize()override;

	void Update()override;


#pragma region get
	vector<shared_ptr<Warp>>GetWarps() { return warps_; }
#pragma endregion


private:

	GameObjectManager* gameObjectManager_ = nullptr;

	vector<shared_ptr<Warp>>warps_ = {};


	uint32_t warpCount_ = 0;
};
