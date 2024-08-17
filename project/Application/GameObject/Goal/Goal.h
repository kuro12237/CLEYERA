#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectManager/IObjectData.h"
#include"GameObject/GameCollider/ICollider.h"
#include"Input.h"
#include"Utility/ObjectId/GameObjectId.h"

class Goal :public IObjectData, public ICollider
{
public:
	Goal() {};
	~Goal() {};

	void Initialize();

	void Update();

	void OnCollision(ICollider* c)override;

	bool GetIsGoalFlag() { return isGoalFlag_; }

private:

	bool isGoalFlag_ = false;

	GameObjectManager* gameObjIncetance_ = nullptr;
};