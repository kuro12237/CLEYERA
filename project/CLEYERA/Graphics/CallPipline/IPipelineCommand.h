#pragma once
#include"GraphicsPipelineManager.h"
#include"CreateResource.h"

/// <summary>
/// �R�}���h�C���^�[�t�F�[�X
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