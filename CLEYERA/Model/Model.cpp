#include "Model.h"

using namespace Math::Vector;

Model::~Model()
{
	delete desc_;
}

void Model::CreateModel(unique_ptr<IModelState> state, Vector4 CenterPos , float size , Vector4 color)
{
	CenterPos_ = CenterPos;
	size_ = size;
	color_ = color;

	state_=move(state);
	state_->Initialize(this);
}

void Model::CreateObj(SModelData modeldata,unique_ptr<IModelState>state)
{
	state_ = move(state);
	modelData_ = modeldata;
	state_->Initialize(this);
}

void Model::CommandCallPipelineVertex()
{
	state_->CallPipelinexVertex(this);
}

void Model::Draw(uint32_t instancingNum)
{
	if (state_ == nullptr)
	{
		LogManager::Log("None SetModel\n");
		assert(0);
	}
	
	state_->Draw(this,instancingNum);
}



