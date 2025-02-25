#pragma once
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"Utility/ObjectId/GameObjectId.h"

/// <summary>
/// マップのブロッククラス
/// </summary>
class Block :public ObjectComponent
{
public:
	Block() {};
	~Block() {};

	/// <summary>
	/// 初期化 
	/// </summary>
	/// <param name="グループ名"></param>
	/// <param name="番号"></param>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 当たった処理
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(ObjectComponent* objData)override;

#pragma region Set

	void SetName(string name) { name_ = name; }
	void SetBlockIndex(uint32_t index) { blockNumber_ = index; }

#pragma endregion


	void SetParticleField(Engine::Particle::ParticleField<Engine::Particle::FieldType::FieldHitBox>* instance) { boxField_ = instance; }

private:

	uint32_t blockNumber_ = 0;

	Engine::Transform::TransformEular initialTransform_{};
	Engine::Particle::ParticleField<Engine::Particle::FieldType::FieldHitBox>*boxField_ = nullptr;

};