#pragma once
#include"Sprite/Sprite.h"

/// <summary>
/// �^�C�g��3d�̃N���X
/// </summary>
class TitleName
{
public:
	TitleName() {};
	~TitleName() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:

	unique_ptr<Engine::Objects::Sprite>sprite_ = nullptr;
	Engine::Transform::WorldTransform worldTransform_ = {};
	uint32_t texHandle_ = 0;

};
