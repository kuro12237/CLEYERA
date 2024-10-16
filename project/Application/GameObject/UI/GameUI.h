#pragma once
#include"Sprite/Sprite.h"

/// <summary>
/// �Q�[������UI
/// </summary>
class GameUI
{
public:
	GameUI() {};
	~GameUI() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// 2d�\��
	/// </summary>
	void Draw2d();

private:

	unique_ptr<Engine::Objects::Sprite>bottonASprite_ = nullptr;
	Engine::Transform::WorldTransform bottonAwT_ = {};
	uint32_t bottonATexhandle_ = 0;

};
