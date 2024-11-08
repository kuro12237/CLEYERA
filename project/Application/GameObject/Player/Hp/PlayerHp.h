#pragma once
#include"Sprite/Sprite.h"

/// <summary>
/// プレイヤーのHp管理
/// </summary>
class PlayerHp
{
public:
	PlayerHp() {};
	~PlayerHp() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="hpの数値"></param>
	void Initialize(uint32_t hp);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// ImGui更新
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// 2d描画
	/// </summary>
	void Draw2d();

	void ReduceHp();

#pragma region Get
	int32_t &GetHp() { return hpCount_; }
#pragma endregion

#pragma region Set

#pragma endregion

private:

	
	int32_t hpCount_ = 0;

	unique_ptr<Engine::Objects::Sprite>sprite_ = nullptr;
	vector<Engine::Transform::WorldTransform>wTs_{};
	uint32_t texHandle_ = 0;

	unique_ptr<Engine::Objects::Sprite>flameSprite_ = nullptr;
	Engine::Transform::WorldTransform flameWorldTransform_ = {};
	uint32_t flameTexHandle_ = 0;
	unique_ptr<Engine::Objects::Sprite>flameNameSprite_ = nullptr;
	Engine::Transform::WorldTransform flameNameWorldTransform_ = {};
	uint32_t flameNameTexHandle_ = 0;
};
