#pragma once
#include"Pch.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"ClearCoin.h"
#include"Utility/ColorConverter/ColorConverter.h"

/// <summary>
/// クリアシーンのコイン管理クラス
/// </summary>
class ClearCoinManager
{
public:
	ClearCoinManager() {};
	~ClearCoinManager() {};


	/// <summary>
	/// 初期化
	/// </summary>
	void Initilaize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();


#pragma region Set
	void CoinsCount(uint32_t coin) { coinCount_ = coin; };
	void SetIsAnimStart(bool f) { isAnimStart_ = f; }
#pragma endregion

#pragma region Get
	bool GetIsAnimStart() { return isAnimStart_; }
#pragma endregion


private:

	/// <summary>
	/// コインをobjectManager二登録
	/// </summary>
	/// <param name="pos"></param>
	void CreateCoinGameObject(const Math::Vector::Vector3 &pos,int32_t index);

	bool isAnimStart_ = false;

	int32_t coinCount_ = 0;
	const size_t coinsMax_ = 3;

	uint32_t modelHandle_ = 0;


	vector<unique_ptr<ClearCoin>>clearCoins_{};

	
};