#pragma once
#include"Sprite/Sprite.h"

/// <summary>
/// �v���C���[��Hp�Ǘ�
/// </summary>
class PlayerHp
{
public:
	PlayerHp() {};
	~PlayerHp() {};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="hp�̐��l"></param>
	void Initialize(uint32_t hp);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ImGui�X�V
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// 2d�`��
	/// </summary>
	void Draw2d();

#pragma region Get
	int32_t &GetHp() { return hpCount_; }
#pragma endregion

private:

	int32_t hpCount_ = 0;

	unique_ptr<Sprite>sprite_ = nullptr;
	vector<WorldTransform>wTs_{};
	uint32_t texHandle_ = 0;

	unique_ptr<Sprite>flameSprite_ = nullptr;
	WorldTransform flameWorldTransform_ = {};
	uint32_t flameTexHandle_ = 0;
	unique_ptr<Sprite>flameNameSprite_ = nullptr;
	WorldTransform flameNameWorldTransform_ = {};
	uint32_t flameNameTexHandle_ = 0;
};
