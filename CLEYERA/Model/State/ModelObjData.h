#pragma once
#include"pch.h"
#include"CreateResource.h"
#include"Model.h"

class ModelObjData
{
public:
	
	ModelObjData(SModelData modelData, uint32_t index, unique_ptr<Model> model) {
		modelData_ = modelData,
			index_ = index;
		model_ = move(model);
	}


	~ModelObjData() {};

	SModelData GetData() { return modelData_; }
	Model* GetModel() { return model_.get(); }

	uint32_t GetIndex() { return index_; }


private:

	unique_ptr<Model>model_;
	SModelData modelData_;
	uint32_t index_;
};