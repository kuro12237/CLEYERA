#pragma once
#include"GameObject/GameCollider/ICollider.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/ObjectId/GameObjectId.h"

class Block :public IObjectData, public ICollider
{
public:
	Block() {};
	~Block() {};

	void Initialize(string name,uint32_t index);

	void Update();

	void OnCollision(ICollider* c)override;

private:

	TransformEular initialTransform_{};

};