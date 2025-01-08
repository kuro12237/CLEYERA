#pragma once
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Graphics/CallPipline/commands/Phong3dPiplineDepthNoneWriteCommand.h"

/// <summary>
/// ステージ番号
/// </summary>
class StageNumber:public IObjectData
{
public:
	StageNumber() {};
	~StageNumber() {};

	void Initialize(uint32_t num);

	void Update();


private:

};

