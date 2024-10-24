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

#pragma region Get

	Player* GetPlayerCore() { return playerCore_.get(); }
	PlayerReticle* GetReticle() { return reticle_.get(); }
	PlayerGun* GetGun() { return gun_.get(); }
	PlayerCamera* GetCamera() { return camera_.get(); }
	PlayerHp* GetHp() { return hp_.get(); }
	vector<shared_ptr<PlayerBullet>>GetBullet() { return bullets_; }
#pragma endregion

#pragma region Set

	void SetStartFlag(bool f) { gameStartFlag_ = f; }

#pragma endregion

	/// <summary>
	/// BUlletの登録
	/// </summary>
	/// <param name="pos"></param>
	void PushBullet(Math::Vector::Vector3 pos);

private:

	/// <summary>
	/// 死んだ弾の確認死んでいたら削除
	/// </summary>
	void CheckisDeadBullets();

	/// <summary>
	/// ダメージを受けた時の処理
	/// </summary>
	void CheckDamage();

	bool gameStartFlag_ = false;

	GameObjectManager* gameObjectManager_ = nullptr;

	unique_ptr<PlayerCommandHandler>commandHandler_ = nullptr;
	unique_ptr<PlayerReticleCommandHandler>reticleCommandHandler_ = nullptr;

	shared_ptr<Player>playerCore_ = nullptr;
	unique_ptr<PlayerReticle>reticle_ = nullptr;
	unique_ptr<PlayerGun>gun_ = nullptr;
	unique_ptr<PlayerCamera>camera_ = nullptr;
	unique_ptr<PlayerHp>hp_ = nullptr;

	bool isHpReductionActive_ = false;
	int32_t kPlayerHp_ = 10;

	vector<shared_ptr<PlayerBullet>>bullets_{};
	queue<uint32_t>deadBulletIndex_;

	Math::Vector::Vector3 playerWorldPos = {};
	const Math::Vector::Vector3* p_ReticleWorldPos_ = nullptr;
};