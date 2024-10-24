#pragma once
#include"pch.h"
#include"CreateResource.h"
#include"Model.h"

class ModelObjData
{
public:

	ModelObjData(SModelData modelData, uint32_t index, unique_ptr<Engine::Objects::Model> model) {
		modelData_ = modelData,
			index_ = index;
		model_ = move(model);
	}


	~ModelObjData() {};

#pragma region Get

	SModelData GetData() { return modelData_; }
	Engine::Objects::Model* GetModel() { return model_.get(); }
	
	/// <summary>
	/// ÉÇÉfÉãî‘çÜ
	/// </summary>
	uint32_t GetIndex() { return index_; }
#pragma endregion

private:

	unique_ptr<Engine::Objects::Model>model_;
	SModelData modelData_;
	uint32_t index_;
};