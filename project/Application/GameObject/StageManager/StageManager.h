#pragma once
#include"Pch.h"

enum class  StageEnum
{
	Stage_1,
	Stage_2,
	Stage_3,
	Stage_4,
	Stage_5,
	Stage_Max
};

/// <summary>
/// ステージ数管理クラス
/// </summary>
class StageManager
{
public:

	static StageManager* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initilaize();

#pragma region Get

	StageEnum GetStage() { return stageNumber_; }
	string GetStringStageFilePath() { return mapName_[stageNumber_]; };

#pragma endregion


#pragma region Set
	void SetStage(const StageEnum& stage) { stageNumber_ = stage; }
#pragma endregion

private:

	StageEnum stageNumber_ = StageEnum::Stage_1;
	StageEnum stageNumberMax_ =StageEnum::Stage_Max;

	map<StageEnum, string>mapName_ = {};

	StageManager() = default;
	~StageManager() = default;
	StageManager(const   StageManager&) = delete;
	const   StageManager& operator=(const StageManager&) = delete;
};
