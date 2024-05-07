#pragma once
#include"Game3dObject.h"
#include"Input.h"
#include"Utility/GameCollisionManager/GameCollider/BoxCollider.h"
#include"Utility/GameGravityManager/IGravity.h"
#include"Utility/GameCollisionManager/GameColliderConfig.h"
#include"Utility/GlobalVariables/GlobalVariables.h"
#include"Utility/ObjectId/GameObjectId.h"
#include"Audio/AudioManager.h"
#include"Utility/CollisionManager/Collider/OBBCollider.h"

#include"Reticle/PlayerReticle.h"
#include"PlayerGun/PlayerGun.h"
#include"Hp/PlayerHp.h"

#include"State/IPlayerState.h"
#include"state/PlayerNormalState.h"
#include"state/PlayerStoneState.h"

enum PlayerBehavior
{
	Normal,
	Stone
};

class Player:public IBoxCollider,public IGravity,public OBBCollider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();

	void Draw(const CameraData& camera);

	void Draw2d(const CameraData& camera);

	void ImGuiUpdate();

	void OnBlockCollision(IBoxCollider* collider)override;
	void OnCollision(uint32_t id)override;

	void GravityExc(const Math::Vector::Vector2 &g)override;

	void ChangeState(unique_ptr<IPlayerState>state);

#pragma region Command

	void Move();

	void Jamp();

	void GunAttack();

#pragma endregion

#pragma region Get

	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	Math::Vector::Vector3 GetWorldPosition()override;
	Math::Vector::Vector3 GetSize()override;
	Math::Vector::Vector3 GetRotate()override;

	const uint32_t &GetHp() { return *hpCount_; }

#pragma endregion

#pragma region Set

	void SetParent(const WorldTransform& w) { worldTransform_.parent = &w; }

	void SetGrayFactor(const float& factor) { game3dObjectdesc_.colorDesc.grayFactor_ = factor; }

	void SetBehavior(PlayerBehavior b) { behavior_ = b; }

#pragma endregion

private:

	//object
	uint32_t modelHandle_ = 0;
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	Game3dObjectDesc game3dObjectdesc_ = {};

	//pos
	Math::Vector::Vector3 GameStartPos_ = {};
	WorldTransform worldTransform_{};

	//colloder
	AABB aabb_ = {};
	Math::Vector::Vector2 velocity_ = {};

	//state
	unique_ptr<IPlayerState>state_ = nullptr;
	PlayerBehavior behavior_ = Normal;

	bool isJamp_ = false;

	
	unique_ptr<PlayerReticle>reticle_ = nullptr;
	unique_ptr<PlayerGun>gun_ = nullptr;

	//hp
	unique_ptr<PlayerHp>hp_ = nullptr;
	const uint32_t* hpCount_ = {};

};

