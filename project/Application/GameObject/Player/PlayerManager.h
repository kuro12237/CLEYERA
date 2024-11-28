#pragma once
#include"Utility/ObjectManager/GameObjectManager.h"

#include"Player.h"
#include"Reticle/PlayerReticle.h"

#include"command/PlayerCommandHandler.h"

#include"Reticle/command/PlayerReticleCommandHandler.h"

#include"Gun/PlayerGun.h"
#include"Bullet/PlayerBullet.h"
#include"PlayerCamera/PlayerCamera.h"
#include"Hp/PlayerHp.h"
#include"Utility/RandomGenerator/RandomGenerator.h"
#include"Bullet/PlayerBulletManager.h"
#include"Particle/PlayerMoveParticle.h"


/// <summary>
/// プレイヤーのオブジェクトの管理クラス
/// </summary>
class PlayerManager
{
public:
	PlayerManager() {};
	~PlayerManager() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// ImGuiの更新
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 2d描画
	/// </summary>
	void Draw2d();

	/// <summary>
	/// Hpの表示
	/// </summary>
	void DrawHp();

	void DrawParticle();

#pragma region Get

	Player* GetPlayerCore() const { return playerCore_.get(); }
	PlayerReticle* GetReticle() const { return reticle_.get(); }
	PlayerGun* GetGun() const{ return gun_.get(); }
	PlayerCamera* GetCamera() const { return camera_.get(); }
	PlayerHp* GetHp() const{ return hp_.get(); }
	vector<shared_ptr<PlayerBullet>>GetBullet() const{ return bullets_; }
#pragma endregion

#pragma region Set
	void SetStartFlag(bool f) { gameStartFlag_ = f; }
#pragma endregion

	/// <summary>
	/// BUlletの登録
	/// </summary>
	/// <param name="pos"></param>
	void PushBullet(const Math::Vector::Vector3& pos);

private:

	/// <summary>
	/// 死んだ弾の確認死んでいたら削除
	/// </summary>
	void CheckisDeadBullets();

	void DamegeUpdate();
	void DamegeUpdateEnd();

	float vinatteFactor_ = 1.0f;

	bool gameStartFlag_ = false;

	GameObjectManager* gameObjectManager_ = nullptr;
	Engine::PostEffect* postEffect_ = nullptr;

	unique_ptr<PlayerCommandHandler>commandHandler_ = nullptr;
	unique_ptr<PlayerReticleCommandHandler>reticleCommandHandler_ = nullptr;

	shared_ptr<Player>playerCore_ = nullptr;
	unique_ptr<PlayerReticle>reticle_ = nullptr;
	unique_ptr<PlayerGun>gun_ = nullptr;
	unique_ptr<PlayerCamera>camera_ = nullptr;
	shared_ptr<PlayerHp>hp_ = nullptr;

	int32_t kPlayerHp_ = 2;


	unique_ptr<PlayerBulletManager>bulletManager_ = nullptr;
	vector<shared_ptr<PlayerBullet>>bullets_{};
	queue<uint32_t>deadBulletIndex_;

	uint32_t bulletModelHandle_ = 0;

	Math::Vector::Vector3 playerWorldPos = {};

	//particle
	unique_ptr<PlayerMoveParticle>moveParticle_ = nullptr;


	bool* isChangeGameOverAnimation_ = nullptr;
	const Math::Vector::Vector3* p_CoreWorldPos_ = nullptr;
	const Math::Vector::Vector3* p_ReticleWorldPos_ = nullptr;
	const Math::Vector::Vector3* p_GunWorldPos_ = nullptr;
};