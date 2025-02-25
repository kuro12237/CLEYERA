#pragma once
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Block.h"
#include"GameObject/ObjectInterface/ManagerComponent.h"

#include"Particle/Field/ParticleField.h"
#include"Particle/Field/StructParticleField.h"
/// <summary>
/// ブロック管理
/// </summary>
class BlockManager :public ManagerComponent
{
public:
	BlockManager() {};
	~BlockManager() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	void Dispach(Engine::Particle::GpuParticle* particle) { boxField_->Dispach(particle); }

#pragma region Get
	vector<shared_ptr<Block>>GetBlocks() { return blocks_; }
#pragma endregion

private:

	string name_ = "Map";

	vector<shared_ptr<Block>>blocks_;

	bool isInitialize = false;

	unique_ptr<Engine::Particle::ParticleField<Engine::Particle::FieldType::FieldHitBox>>boxField_ = nullptr;

};

