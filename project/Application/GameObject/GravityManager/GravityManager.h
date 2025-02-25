#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"Particle/Field/ParticleField.h"
#include"GameObject/ObjectInterface/ManagerComponent.h"

/// <summary>
/// 重力処理を
/// </summary>
class GravityManager :public ManagerComponent
{
public:
	GravityManager() {};
	~GravityManager() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	void PushParticleList(Engine::Particle::GpuParticle* p) { particles_.push_back(p); }

	/// <summary>
	/// リスト削除
	/// </summary>
	void ClearList() { objectDatas_.clear(); particles_.clear(); }

	/// <summary>
	/// リスト登録
	/// </summary>
	/// <param name="data"></param>
	void PushList(ObjectComponent* data) { objectDatas_.push_back(data); }

	/// <summary>
	/// 重力処理
	/// </summary>
	void CheckGravity();

#pragma region Get

	Engine::Particle::ParticleField<Engine::Particle::FieldType::FieldGravity>* GetParticleGravityField() { return particleGravityField_.get(); }

#pragma endregion


private:

	list<ObjectComponent*>objectDatas_;

	list<Engine::Particle::GpuParticle*>particles_;

	float gravity_ = 0.05f;

	unique_ptr<Engine::Particle::ParticleField<Engine::Particle::FieldType::FieldGravity>>particleGravityField_ = nullptr;

};

