#pragma once
#include"Game3dObject.h"
#include"WorldTransform.h"

#include"Game3dInstancingObject/GameInstancing3dObject.h"
#include"Transform/STransformEular.h"
#include"IGameObjectData.h"

class  Game3dObjectData:public IGameObjectData
{
public:

	
	void Initialize(Engine::Transform::TransformEular transform, Game3dObjectDesc desc, uint32_t modelHandle);

	void WtUpdate(Engine::Transform::TransformEular transform);

#pragma region Set

	void SetData(Game3dObjectData* data);
	void SetModelName(string name) { modelFileName_ = name; }
	void SetGameObject(unique_ptr<Engine::Objects::Game3dObject> data) { gameObject_ = move(data); }
	void SetGameObjeDesc(Game3dObjectDesc desc) { gameObject_->SetDesc( desc); }
	void SetModelHandle(uint32_t handle) { modelHandle_ = handle; }

	void ChangePipline(unique_ptr<IPipelineCommand> piplineSelect);
	void SetTexHandle(uint32_t handle) { gameObject_->SetTexHandle(handle); }
#pragma endregion

#pragma region Get

	unique_ptr<Engine::Objects::Game3dObject>& GetGameObject() { return gameObject_; }
	Game3dObjectDesc &GetDesc() { return gameObjectDesc_; }
	uint32_t GetModelHandle() { return modelHandle_; }
#pragma endregion

private:

	std::string modelFileName_;
	unique_ptr<Engine::Objects::Game3dObject>gameObject_;
	uint32_t modelHandle_ = 0;

	SAnimation::Skeleton skelton_ = {};
	SAnimation::Animation animationData_;

	Game3dObjectDesc gameObjectDesc_;
	float animationFlame_ = 0.0f;
};

