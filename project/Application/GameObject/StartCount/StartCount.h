#pragma once
#include"Cleyera.h"

/// <summary>
/// ゲームカウントダウン
/// </summary>
class StartCount
{
public:
	StartCount() {};
	~StartCount() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 2d表示
	/// </summary>
	void Draw2d();

#pragma region Get
	bool GetStartFlag() { return startFlag_; };
#pragma endregion

#pragma region Set
	void SetStartFlag(bool f) { startFlag_ = f; }
#pragma endregion

private:

	/// <summary>
	/// 数字の更新
	/// </summary>
	void NumberUpdate();

	/// <summary>
	/// 針の更新
	/// </summary>
	void BarUpdate();

	/// <summary>
	/// 数字の後ろの背景更新
	/// </summary>
	void FlameUpdate();

	unique_ptr<Sprite>numberSprite_ = nullptr;
	WorldTransform numberWorldTransform_ = {};
	uint32_t numberTex_ = 0;

	float numberAnimationFlame_ = 0.0f;

	uint32_t timerCount = 0;
	uint32_t timerCountMax = 3;

	bool startFlag_ = false;
	bool countUpdateFlag_ = false;
	bool countDrawFlag_ = false;

	vector<unique_ptr<Sprite>>flameSprites_ = {};
	vector<WorldTransform>flameWts_;
	uint32_t flameTex_ = 0;

	vector<Math::Vector::Vector3> startFlamePos_;
	vector<Math::Vector::Vector2>endFlamePos_;

	unique_ptr<Sprite>backFlameSprite_ = nullptr;
	WorldTransform backFlameWt_;
	uint32_t backFlameTex_ = 0;

	size_t BarMax = 11;
	uint32_t barTex_ = 0;
	vector<unique_ptr<Sprite>>barSprites_ = {};
	vector<WorldTransform>barWts_;
	uint32_t barCount_ = 0;
};