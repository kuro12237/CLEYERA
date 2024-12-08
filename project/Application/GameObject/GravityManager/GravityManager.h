#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Particle/Field/ParticleField.h"

/// <summary>
/// 重力処理を
/// </summary>
class GravityManager
{
public:
	GravityManager() {};
	~GravityManager() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initilaize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void PushParticleList(Engine::Particle::GpuParticle* p) { particles_.push_back(p);}

	/// <summary>
	/// リスト削除
	/// </summary>
	void ClearList() { objectDatas_.clear(); particles_.clear(); }

	/// <summary>
	/// リスト登録
	/// </summary>
	/// <param name="data"></param>
	void PushList(IObjectData* data) { objectDatas_.push_back(data); }

	/// <summary>
	/// 重力処理
	/// </summary>
	void CheckGravity();

private:

	list<IObjectData*>objectDatas_;

	list<Engine::Particle::GpuParticle*>particles_;

	float gravity_ = 0.01f;

	unique_ptr<Engine::Particle::ParticleField<Engine::Particle::FieldType::FieldGravity>>particleGravityField_ = nullptr;

};

