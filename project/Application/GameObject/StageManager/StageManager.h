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

class StageManager
{
public:

	static StageManager* GetInstance();

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initilaize();

	StageEnum GetStage() { return stageNumber_; }
	string GetStringStageFilePath() { return mapName_[stageNumber_]; };
	
	void SetStage(const StageEnum& stage) { stageNumber_ = stage; }

private:

	StageEnum stageNumber_ = StageEnum::Stage_1;
	StageEnum stageNumberMax_ =StageEnum::Stage_Max;

	map<StageEnum, string>mapName_ = {};

	StageManager() = default;
	~StageManager() = default;
	StageManager(const   StageManager&) = delete;
	const   StageManager& operator=(const StageManager&) = delete;
};
