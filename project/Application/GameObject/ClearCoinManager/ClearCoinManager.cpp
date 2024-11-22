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
	for (unique_ptr<ClearCoin>&coin : clearCoins_)
	{
		coin->Update();
	}
}

void ClearCoinManager::CreateCoinGameObject(const Math::Vector::Vector3& pos,int32_t index)
{
	//オブジェクトの作成
	string coinName = "Coin";
	shared_ptr<Game3dObjectData> data = make_shared<Game3dObjectData>();
	data->SetObjectType("ARMATURE");
	const float kScale = 0.5f;
	Engine::Transform::TransformEular transform = { .scale{kScale,kScale,kScale},.rotate{}};
	transform.translate.y = 3.5f;

	if (index == 0)
	{
		transform.translate.x = -1.5f;
	}
	if (index == 1)
	{
		transform.translate.x = 1.5f;
	}

	string name_num = coinName + to_string(index);
	data->SetObjName(name_num);
	data->SetModelFilePath("StageCoin");
	data->Initialize(transform, {}, modelHandle_);

	GameObjectManager::GetInstance()->PushObj3dData(data, name_num);

	unique_ptr<ClearCoin>coin = make_unique<ClearCoin>();
	coin->SetName(name_num);

	if (index < coinCount_)
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
