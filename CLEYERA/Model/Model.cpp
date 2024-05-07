#include "Model.h"

using namespace Math::Vector;

Model::~Model()
{
}

void Model::CreateModel(unique_ptr<IModelState> state, Vector4 CenterPos , float size , Vector4 color)
{
	CenterPos_ = CenterPos;
	size_ = size;
	color_ = color;

	state_=move(state);
	state_->Initialize(this);
}

void Model::SetModel(uint32_t handle)
{
	prevModelHandle_ = modelHandle_;
	modelHandle_ = handle;

	if (prevModelHandle_ != modelHandle_)
	{
		state_=make_unique<ModelObjState>();
		state_->Initialize(this);
	}
}

void Model::CreateObj(SModelData modeldata)
{
	state_ = make_unique<ModelObjState>();
	modelData_ = modeldata;
	state_->Initialize(this);
}

void Model::CommandCallPipelineVertex()
{
	state_->CallPipelinexVertex(this);
}

void Model::Draw(const CameraData& viewprojection, uint32_t instancingNum)
{
	if (state_ == nullptr)
	{
		LogManager::Log("None SetModel\n");
		assert(0);
	}
	
	state_->Draw(this,viewprojection,instancingNum);
}



