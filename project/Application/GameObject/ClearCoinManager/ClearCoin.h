#pragma once
#include"GameObject/ObjectInterface/IObjectData.h"
#include"state/ClearCoinStateActive.h"
#include"state/IClearCoinState.h"

enum class CoinDirection
{
	Left,
	Center,
	Rignt
};

enum class CoinUse
{
	Active,
	Inactive
};


/// <summary>
/// クリアコイン制御クラス
/// </summary>
class ClearCoin:public IObjectData
{
public:
	ClearCoin() {};
	~ClearCoin() {};

	void Initialize(const CoinUse&use);

	void Update();

#pragma region Set
	void StartAnimation(bool isStart) { isStart_ = isStart; }
	
#pragma endregion

private:

	const Math::Vector::Vector3* cameraPos_ = nullptr;

	bool isStart_ = false;
	unique_ptr<IClearCoinState>state_ = nullptr;
};
