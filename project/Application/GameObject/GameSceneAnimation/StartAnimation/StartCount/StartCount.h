#pragma once
#include"Cleyera.h"

/// <summary>
/// �Q�[���J�E���g�_�E��
/// </summary>
class StartCount
{
public:
	StartCount() {};
	~StartCount() {};

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

#pragma region Get
	bool GetStartFlag() { return startFlag_; };
	bool GetIsNumberChange() { return isNumberChange_; }
#pragma endregion

#pragma region Set
	void SetStartFlag(bool f) { startFlag_ = f; }
#pragma endregion

private:

	/// <summary>
	/// �����̍X�V
	/// </summary>
	void NumberUpdate();

	/// <summary>
	/// �j�̍X�V
	/// </summary>
	void BarUpdate();

	/// <summary>
	/// �����̌��̔w�i�X�V
	/// </summary>
	void FlameUpdate();

	unique_ptr<Engine::Objects::Sprite>numberSprite_ = nullptr;
	Engine::Transform::WorldTransform numberWorldTransform_ = {};
	uint32_t numberTex_ = 0;

	float numberAnimationFlame_ = 0.0f;

	uint32_t timerCount = 0;
	uint32_t timerCountMax = 3;

	bool startFlag_ = false;
	bool countUpdateFlag_ = false;
	bool countDrawFlag_ = false;

	bool isNumberChange_ = false;

	vector<unique_ptr<Engine::Objects::Sprite>>flameSprites_ = {};
	vector<Engine::Transform::WorldTransform>flameWts_;
	uint32_t flameTex_ = 0;

	vector<Math::Vector::Vector3> startFlamePos_;
	vector<Math::Vector::Vector2>endFlamePos_;

	unique_ptr<Engine::Objects::Sprite>backFlameSprite_ = nullptr;
	Engine::Transform::WorldTransform backFlameWt_;
	uint32_t backFlameTex_ = 0;

	size_t BarMax = 11;
	uint32_t barTex_ = 0;
	vector<unique_ptr<Engine::Objects::Sprite>>barSprites_ = {};
	vector<Engine::Transform::WorldTransform>barWts_;
	uint32_t barCount_ = 0;

	TransformEular easeOutExpoMin_;
	TransformEular easeOutExpoMax_;
};