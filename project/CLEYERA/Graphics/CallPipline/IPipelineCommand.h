#pragma once
#include"GraphicsPipelineManager.h"
#include"CreateResource.h"

/// <summary>
/// コマンドインターフェース
/// </summary>
class IPipelineCommand
{
public:
	IPipelineCommand() {};
	virtual ~IPipelineCommand() {};

	virtual void Exec(const SModelData& modelData) = 0;

	void SetPso(SPSOProperty pso) { pso_ = pso; }

	void CallCommand();

private:
	SPSOProperty pso_;
};