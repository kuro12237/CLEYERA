#include "Arch.h"

void Arch::Initialize()
{

	name_ = "ArchBridge";

	auto& desc = gameObjectManager_->GetObjectDesc(name_);

	//edgeÝ’è
	desc.edgeDesc.minmax = { -0.1f,0.2f };
	desc.edgeDesc.mask = 1.0f;
	desc.edgeDesc.edgeColor = { 0.0f,0.0f,1.0f,0.0f };
}

void Arch::Update()
{
	if (isStart_)
	{
		auto& desc = gameObjectManager_->GetObjectDesc(name_);
		if (desc.edgeDesc.mask >= 0.0f)
		{
			desc.edgeDesc.mask -= 1.0f / 120.0f;
		}
	}

}
