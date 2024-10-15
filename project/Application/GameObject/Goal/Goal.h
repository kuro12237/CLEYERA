#pragma once
#include"STransformEular.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"GameObject/GameCollider/ICollider.h"
#include"Input.h"
#include"Utility/ObjectId/GameObjectId.h"
#include"Particle/GoalParticle.h"
#include"Graphics/CallPipline/PipelineHandler.h"

/// <summary>
/// ゴールクラス
/// </summary>
class Goal :public IObjectData, public ICollider
{
public:
	Goal() {};
	~Goal() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(uint32_t id, uint32_t index);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 当たった時
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(ICollider* c)override;

#pragma region Get
	bool GetIsGoalFlag() { return isGoalFlag_; }
#pragma endregion

private:

	string portalName_ = "GoalPortal";
	string backName_ = "GoalBack";

	bool isGoalFlag_ = false;
	uint32_t index_ = 0;

	GameObjectManager* gameObjIncetance_ = nullptr;
};