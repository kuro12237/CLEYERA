#pragma once
#include"IModelState.h"
#include"Model.h"
#include"ModelManager.h"
#include"VectorTransform.h"
#include"Light/LightingManager.h"

class ModelObjState :public IModelState
{
public:
	ModelObjState() {};
	~ModelObjState() ;

	void Initialize(Model* state)override;
	void CallPipelinexVertex(Model* state)override;
	void Draw(Model* state,const CameraData& viewprojection)override;

private:
	ResourcePeroperty resource_ = {};
};