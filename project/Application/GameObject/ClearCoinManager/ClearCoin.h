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

	void ChangeState(unique_ptr<IClearCoinState>state);

	void CreateState();

#pragma region Set
	void StartAnimation(bool isStart) { isStart_ = isStart; }
	void SetIsEnd(bool f) { isEnd_ = f; }
#pragma endregion

#pragma region Get
	bool GetIsStateAnimation() { return isStart_; }
	bool GetIsEnd() { return isEnd_; }

#pragma endregion

private:

	CoinUse isUse_;

	const Math::Vector::Vector3* cameraPos_ = nullptr;

	bool isEnd_ = false;
	bool isStart_ = false;
	unique_ptr<IClearCoinState>state_ = nullptr;
};
