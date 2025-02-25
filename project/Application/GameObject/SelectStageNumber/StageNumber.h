#pragma once
#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"Graphics/CallPipline/commands/Phong3dPiplineDepthNoneWriteCommand.h"

/// <summary>
/// ステージ番号
/// </summary>
class StageNumber:public ObjectComponent
{
public:
	StageNumber() {};
	~StageNumber() {};

	void Initialize()override;

	void Update()override;

	void SetNum(uint32_t num) { number_ = num; }

private:
	uint32_t number_ = 0;
};

