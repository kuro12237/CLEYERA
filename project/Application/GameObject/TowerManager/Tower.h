#pragma once
#include"GameObject/GameCollider/ICollider.h"
#include"Utility/ObjectId/GameObjectId.h"

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"

class Tower :public IObjectData
{
public:
	Tower() {};
	~Tower() {};

	void Initialize(string name, uint32_t index);

	void Update();

#pragma region Set

	void SetPos(const Math::Vector::Vector3& newPos);

#pragma endregion


private:

	uint32_t index_ = 0;
	GameObjectManager* gameObjectManager_ = nullptr;
	TransformEular initialTransform_ = {};
	Math::Vector::Vector3 newPos_ = {};
	bool isSetNewPos_ = false;
};