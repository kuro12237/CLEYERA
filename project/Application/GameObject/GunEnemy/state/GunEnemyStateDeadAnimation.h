#pragma once
#include"IGunEnemyState.h"
#include"../GunEnemy.h"

#include"GunEnemyStateShoot.h"
#include"Utility/RandomGenerator/RandomGenerator.h"

#include"GameObject/Particles/CharacterDeadParticle.h"


/// <summary>
/// 死ぬ状態
/// </summary>
class GunEnemyStateDeadAnimation :public IGunEnemyState
{
public:
	GunEnemyStateDeadAnimation() {};
	~GunEnemyStateDeadAnimation() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="本体"></param>
	void Initialize(IGunEnemy* e);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="本体"></param>
	void Update(IGunEnemy* e);
private:

	array<Math::Vector::Vector3,4>impactVec_ = {};
	
	vector<Engine::Transform::TransformEular*>transforms_;

	GameObjectManager* gameObjectManager_ = nullptr;
	float flame_ = 0.0f;
	float flameMax_ = 1.0f;
	float flameAdd_ = 1.0f / 120.0f;
	float nextCallTime_ = 0.0f;

	int32_t deltaTime_ = 0;
	int32_t deltaTimerMax_ = 3;
};
