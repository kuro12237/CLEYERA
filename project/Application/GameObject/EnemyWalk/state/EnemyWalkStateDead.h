#pragma once
#include"IEnemyWalkState.h"
#include"../EnemyWalk.h"
#include"GameObject/Particles/CharacterDeadParticle.h"

/// <summary>
/// 歩く敵の死んだときの状態
/// </summary>
class EnemyWalkStateDead :public IEnemyWalkState
{
public:
	EnemyWalkStateDead() {};
	~EnemyWalkStateDead() {};

	void Initialize([[maybe_unused]] EnemyWalk* e)override;

	void Update([[maybe_unused]] EnemyWalk* e)override;

private:

	GameObjectManager* gameObjIncetance_ = nullptr;
	float flame_ = 0.0f;
	float flameMax_ = 1.0f;
	float flameAdd_ = 1.0f / 120.0f;

	uint32_t particleIndex_ = 0;

	Math::Vector::Vector3 impactDirection_ = { 0.1f,0.4f,0.0f };
};
