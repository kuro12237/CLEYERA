#include "StageManager.h"

StageManager* StageManager::GetInstance()
{
	static StageManager instance; return &instance;
}

void StageManager::Initilaize()
{
	mapName_[StageEnum::Stage_1] = "GameScene_1.json";
	mapName_[StageEnum::Stage_2] = "GameScene_2.json";
	mapName_[StageEnum::Stage_3] = "GameScene_3.json";
	mapName_[StageEnum::Stage_4] = "GameScene_4.json";
	mapName_[StageEnum::Stage_5] = "GameScene_5.json";
}
