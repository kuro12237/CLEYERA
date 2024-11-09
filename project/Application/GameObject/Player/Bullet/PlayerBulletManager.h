#pragma once
#include"PlayerBullet.h"
#include"Utility/RandomGenerator/RandomGenerator.h"
#include"Sprite/Sprite.h"

/// <summary>
/// プレイヤーの弾管理クラス
/// </summary>
class PlayerBulletManager
{
public:
	PlayerBulletManager() {};
	~PlayerBulletManager() {};

	void Initialize();

	void ImGuiUpdate();

	void Update();

	void Draw2d();

	void BulletCountAdd(const int32_t count = 1) { bulletCount_ += count; }

	int32_t GetBulletCount()const { return bulletCount_; }

private:

	int32_t bulletCount_ = 0;
	int32_t bulletCountMax_ = 5;

	int32_t deltaCount_ = 0;
	float flame_ = 0.0f;

	unique_ptr<Engine::Objects::Sprite>bulletSprite_ = nullptr;
	vector<Engine::Transform::WorldTransform>worldTransforms_;
	uint32_t texHandle_ = 0;
};