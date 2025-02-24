#include "WarpManager.h"

void WarpManager::Initialize()
{
	gameObjectManager_ = GameObjectManager::GetInstance();


	const string name = "WarpGate";

	for (uint32_t index = 0; index < uint32_t(gameObjectManager_->GetObj3dDatas().size()); index++)
	{
		string count = to_string(warpCount_);

		string warpName = "";
		if (count == "0")
		{
			warpName = name;
		}
		else {
			warpName = name + "." + string(3 - to_string(warpCount_).length(), '0') + to_string(warpCount_);
		}

		if (gameObjectManager_->GetObj3dDatas().find(warpName) != gameObjectManager_->GetObj3dDatas().end())
		{
			//偶数の時に作成
			if (warpCount_ % 2 == 1)
			{

				warpCount_++;
				continue;
			}
			auto obj = gameObjectManager_->GetObj3dData(warpName);
			//作成
			shared_ptr<Warp>warp = make_shared<Warp>();
			warp->Initlaize(warpCount_);
			warps_.push_back(move(warp));

			warpCount_++;
		}
		else
		{
			break;
		}
	}

}

void WarpManager::Update()
{
	for (shared_ptr<Warp>& warp : warps_)
	{
		warp->Update();
	}
}


