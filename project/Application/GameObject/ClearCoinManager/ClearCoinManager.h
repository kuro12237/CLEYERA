#pragma once
#include"Pch.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"ClearCoin.h"
#include"Utility/ColorConverter/ColorConverter.h"
#include"Particle/ClearCoinSplashParticle.h"
#include"GameObject/ObjectInterface/ManagerComponent.h"

/// <summary>
/// クリアシーンのコイン管理クラス
/// </summary>
class ClearCoinManager:public ManagerComponent
{
public:
	ClearCoinManager() {};
	~ClearCoinManager() {};


	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// パーティクル表示
	/// </summary>
	void ParticleDraw();

	void ImGuiUpdate();


#pragma region Set
	void CoinsCount(uint32_t coin) { coinCount_ = coin; };
	void SetIsAnimStart(bool f) { isAnimStart_ = f; }
#pragma endregion

#pragma region Get
	bool GetIsAnimStart() { return isAnimStart_; }
	bool GetIsComplete() { return isComplete_; }
#pragma endregion


private:


	enum class CoinDirection{
		Left,
		Center,
		Rigft
	};

	/// <summary>
	/// コインをobjectManager二登録
	/// </summary>
	/// <param name="pos"></param>
	void CreateCoinGameObject(const Math::Vector::Vector3 &pos,int32_t index);

	bool isAnimStart_ = false;
	bool isComplete_ = false;
	float particleEmitFlame_ = 0.0f;
	float particleEmitMax_ = 1.0f;

	int32_t coinCount_ = 0;
	const size_t coinsMax_ = 3;

	uint32_t modelHandle_ = 0;
	uint32_t auraModelHandle_ = 0;

	vector<unique_ptr<ClearCoin>>clearCoins_{};

	unique_ptr<ClearCoinSplashParticle>splashParticle_ = nullptr;

	const int32_t useEmitterIndex_ = 0;
};
