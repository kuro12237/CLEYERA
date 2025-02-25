#pragma 
#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"Cleyera.h"
#include"../Player.h"

/// <summary>
/// プレイヤーの銃
/// </summary>
class PlayerGun:public ObjectComponent
{
public:
	PlayerGun() {};
	~PlayerGun() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

#pragma region Set

	void SetTarget(const Math::Vector::Vector3 &t) { targetPos_ = &t; }
	void SetPlayerPos(const Math::Vector::Vector3& pos) { playerPos_ = &pos; }
	void SetPlayerVelo(const Math::Vector::Vector3& velo) { playerVelo_ = &velo; }

	void SetIsDraw(bool flag) { gameObjectManager_->GetObj3dData(name_)->SetIsDraw(flag); }
	void SetPlayer(shared_ptr<Player>p) { player_ = p; }
#pragma endregion

private:

	weak_ptr<Player>player_;

	float kRadious_ = 3.0f;

	const Math::Vector::Vector3 *targetPos_ = {};
	const Math::Vector::Vector3* playerVelo_ = nullptr;
	const Math::Vector::Vector3* playerPos_ = nullptr;

	Math::Vector::Vector3 gunPos_ = {};
};