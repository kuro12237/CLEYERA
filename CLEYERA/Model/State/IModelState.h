#pragma once
#include"WorldTransform.h"

class Model;
class IModelState
{
public:
	virtual ~IModelState() {};
	virtual void Initialize(Model *state) = 0;

	
	virtual void CallPipelinexVertex(Model *state) = 0;
	virtual void Draw(Model* state, const CameraData& viewprojection) = 0;
private:

};

