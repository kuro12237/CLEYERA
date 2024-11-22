#include "ClearCoinManager.h"

void ClearCoinManager::Initilaize()
{
	modelHandle_ = Engine::Manager::ModelManager::LoadGltfFile("StageCoin");

	clearCoins_.resize(3);

	for (int32_t index = 0; index < coinsMax_; index++)
	{
		this->CreateCoinGameObject({ 0.0f,0.0f,0.0f }, index);
	}


}

void ClearCoinManager::Update()
{
	if (isAnimStart_ && !clearCoins_[static_cast<int>(CoinDirection::Left)]->GetIsStateAnimation())
	{
		clearCoins_[static_cast<int>(CoinDirection::Left)]->StartAnimation(true);
		clearCoins_[static_cast<int>(CoinDirection::Left)]->CreateState();
	}


	for (size_t i = 0; i < clearCoins_.size(); ++i)
	{
		unique_ptr<ClearCoin>& coin = clearCoins_[i];
		coin->Update();

		if (coin->GetIsEnd())
		{
			// 現在のコインが終了した際の処理
			if (i + 1 < clearCoins_.size())
			{
				// 次のコインにアクセス
				unique_ptr<ClearCoin>& nextCoin = clearCoins_[i + 1];
				if (!nextCoin->GetIsStateAnimation())
				{
					nextCoin->StartAnimation(true);
					nextCoin->CreateState();
				}
			}
		}

	}
}

void ClearCoinManager::CreateCoinGameObject(const Math::Vector::Vector3& pos, int32_t index)
{
	//オブジェクトの作成
	const float kScale = 0.5f;
	Engine::Transform::TransformEular transform = { .scale{kScale,kScale,kScale},.rotate{} };
	Math::Vector::Vector3 offset = { 0.0f,4.0f,-2.0f };
	transform.translate = offset;

	if (index == 0)
	{
		transform.translate.x = -2.0f;
	}
	if (index == 2)
	{
		transform.translate.x = 2.0f;
	}

	string coinName = "Coin";
	string name_num = coinName + to_string(index);

	for (size_t i = 0; i < 2; i++)
	{
		name_num = coinName + to_string(index + i * 3);

		shared_ptr<Game3dObjectData> data = make_shared<Game3dObjectData>();
		data->SetObjectType("ARMATURE");
		data->SetIsDraw(false);
		data->SetObjName(name_num);
		data->SetModelFilePath("StageCoin");
		data->Initialize(transform, {}, modelHandle_);
		if (i >= 1)
		{
			data->SetIsDraw(true);
			data->GetDesc().colorDesc.color_ = { 0.0f,0.0f,0.0f,0.25f };
		}
		else
		{
			data->GetDesc().colorDesc.color_ = ColorConverter::ColorConversion(0xffd700ff);
		}
		data->ChangePipline(make_unique<Phong3dSkinningPiplineDepthNoneWriteCommand>());
		GameObjectManager::GetInstance()->PushObj3dData(data, name_num);
	}

	name_num = coinName + to_string(index);

	unique_ptr<ClearCoin>coin = make_unique<ClearCoin>();
	coin->SetName(name_num);

	if (index <= coinCount_ - 1)
	{
		coin->Initialize(CoinUse::Active);
	}
	else
	{
		coin->Initialize(CoinUse::Inactive);
	}
	pos;
	clearCoins_[index] = move(coin);
}
