#pragma once
#include"GameObject/ObjectInterface/IParticleData.h"

/// <summary>
/// キャラクターの動く時のパーティクル
/// </summary>
class PlayerMoveParticle :public IParticleData
{
public:

	PlayerMoveParticle() {};
	~PlayerMoveParticle() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

#pragma region Set

	void SetPlayerPos(const Math::Vector::Vector3& pos) { playerWorldPos_ = &pos; }

	void SetIsEmit(bool f) { isEmit_ = f; };
#pragma endregion

private:

	const Math::Vector::Vector3* playerWorldPos_ = nullptr;

	bool isEmit_ = false;
};

