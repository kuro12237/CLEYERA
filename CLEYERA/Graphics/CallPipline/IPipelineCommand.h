#pragma once
#include"GraphicsPipelineManager.h"

class IPipelineCommand
{
public:
	IPipelineCommand() {};
	virtual ~IPipelineCommand() {};

	virtual void Exec() = 0;

	void SetPso(SPSOProperty pso) { pso_ = pso; }

	void CallCommand();

private:
	SPSOProperty pso_;
};