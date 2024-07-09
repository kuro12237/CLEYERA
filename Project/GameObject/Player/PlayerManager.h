#pragma once
#include"GameObject/ObjectManager/GameObjectManager.h"
#include"Player.h"
#include"Reticle/PlayerReticle.h"

#include"command/PlayerCommandHandler.h"
#include"Reticle/command/PlayerReticleCommandHandler.h"
#include"Gun/PlayerGun.h"
#include"Bullet/PlayerBullet.h"
#include"Utility/RandomGenerator/RandomGenerator.h"
#include"PlayerCamera/PlayerCamera.h"

class PlayerManager
{
public:
	PlayerManager() {};
	~PlayerManager() {};

	void GetData(GameObjectManager* data);

	void ImGuiUpdate();

	void Update();

	void Draw2d();

#pragma region Get

	Player* GetPlayerCore() { return playerCore_.get(); }

	PlayerReticle* GetReticle() { return reticle_.get(); }

	PlayerGun* GetGun() { return gun_.get(); }

	PlayerCamera* GetCamera(){ return camera_.get(); }

	vector<shared_ptr<PlayerBullet>>GetBullet() { return bullets_; }
#pragma endregion

	void PushBullet(Math::Vector::Vector3 pos);

private:

	void CheckisDeadBullets();

	unique_ptr<PlayerCommandHandler>commandHandler_ = nullptr;
	unique_ptr<PlayerReticleCommandHandler>reticleCommandHandler_ = nullptr;

	Math::Vector::Vector3 Player_Reticle_ = {};

	shared_ptr<Player>playerCore_ = nullptr;
	unique_ptr<PlayerReticle>reticle_ = nullptr;
	unique_ptr<PlayerGun>gun_ = nullptr;
	unique_ptr<PlayerCamera>camera_ = nullptr;

	vector<shared_ptr<PlayerBullet>>bullets_{};
	queue<uint32_t>deadBulletIndex_;

	Math::Vector::Vector3 playerWorldPos = {};
	Math::Vector::Vector3 reticleWorldPos = {};
};