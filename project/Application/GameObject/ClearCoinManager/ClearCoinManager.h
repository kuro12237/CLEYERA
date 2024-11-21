#pragma once
#include"Pch.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"ClearCoin.h"

/// <summary>
/// �N���A�V�[���̃R�C���Ǘ��N���X
/// </summary>
class ClearCoinManager
{
public:
	ClearCoinManager() {};
	~ClearCoinManager() {};


	/// <summary>
	/// ������
	/// </summary>
	void Initilaize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();


#pragma region Set
	void CoinsCount(uint32_t coin) { coinCount_ = coin; };
#pragma endregion

private:

	/// <summary>
	/// �R�C����objectManager��o�^
	/// </summary>
	/// <param name="pos"></param>
	void CreateCoinGameObject(const Math::Vector::Vector3 &pos,int32_t index);

	int32_t coinCount_ = 0;
	const size_t coinsMax_ = 3;

	uint32_t modelHandle_ = 0;


	vector<unique_ptr<ClearCoin>>clearCoins_{};

	
};
