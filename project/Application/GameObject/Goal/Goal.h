#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectManager/IObjectData.h"
#include"GameObject/GameCollider/ICollider.h"
#include"Input.h"
#include"Utility/ObjectId/GameObjectId.h"
#include"Particle/GoalParticle.h"
#include"Graphics/CallPipline/PipelineHandler.h"
class Goal :public IObjectData, public ICollider
{
public:
	Goal() {};
	~Goal() {};

	void Initialize(uint32_t id, uint32_t index);

	void Update();

	void OnCollision(ICollider* c)override;

	bool GetIsGoalFlag() { return isGoalFlag_; }


private:

	string portalName_ = "GoalPortal";
	string backName_ = "GoalBack";

	bool isGoalFlag_ = false;
	uint32_t index_ = 0;

	GameObjectManager* gameObjIncetance_ = nullptr;
};