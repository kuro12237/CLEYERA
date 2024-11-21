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

/// <summary>
/// �v���C���[�̃I�u�W�F�N�g�̊Ǘ��N���X
/// </summary>
class PlayerManager
{
public:
	PlayerManager() {};
	~PlayerManager() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ImGui�̍X�V
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// 2d�`��
	/// </summary>
	void Draw2d();

	/// <summary>
	/// Hp�̕\��
	/// </summary>
	void DrawHp();

	void DrawParticle();

#pragma region Get

	Player* GetPlayerCore() const { return playerCore_.get(); }
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
	/// BUllet�̓o�^
	/// </summary>
	/// <param name="pos"></param>
	void PushBullet(Math::Vector::Vector3 pos);

private:

	/// <summary>
	/// ���񂾒e�̊m�F����ł�����폜
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

	bool isHpReductionActive_ = false;
	int32_t kPlayerHp_ = 2;

	bool* isChangeGameOverAnimation_ = nullptr;

	unique_ptr<PlayerBulletManager>bulletManager_ = nullptr;
	vector<shared_ptr<PlayerBullet>>bullets_{};
	queue<uint32_t>deadBulletIndex_;

	uint32_t bulletModelHandle_ = 0;

	Math::Vector::Vector3 playerWorldPos = {};
	const Math::Vector::Vector3* p_ReticleWorldPos_ = nullptr;

	const Math::Vector::Vector3* p_GunWorldPos_ = nullptr;
};