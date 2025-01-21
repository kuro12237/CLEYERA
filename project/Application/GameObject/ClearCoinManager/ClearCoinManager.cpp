#include "ClearCoinManager.h"

void ClearCoinManager::Initialize()
{
	modelHandle_ = Engine::Manager::ModelManager::LoadGltfFile("StageCoin");
	auraModelHandle_ = Engine::Manager::ModelManager::LoadObjectFile("StageCoinAura");
	const int32_t sizeMax = 3;
	clearCoins_.resize(sizeMax);

	for (int32_t index = 0; index < coinsMax_; index++)
	{
		this->CreateCoinGameObject({}, index);
	}

	splashParticle_ = make_unique<ClearCoinSplashParticle>();
	splashParticle_->Initialize();

	///パーティクルエディターを作る一旦そのまま

	auto& emit = splashParticle_->GetEmitter()[0];
	auto& control = splashParticle_->GetEmitter()->GetControlParam();
	control[0].frequencyTime = 0.01f;
	control[0].useFlag_ = false;

	auto& param = emit.GetEmitParam()[0];
	param.count = 3;
	param.sizeMax = { 0.1f,0.1f,0.0f };
	param.sizeMin = { -0.1f,-0.1f,0.0f };
	param.velocityMin = { -0.1f,-0.1f,0.0f };
	param.velocityMax = { 0.1f,0.1f,0.0f };
	param.scaleVelocityMax = { -0.01f,-0.01f,0.0f };
	param.scaleVelocityMin = { -0.01f,-0.01f,0.0f };
	param.scaleSizeMin = { 0.1f,0.0f,0.0f };
	param.scaleSizeMax = { 0.2f,0.0f,0.0f };
	param.colorDecayMax.w = 0.05f;
	param.colorDecayMin.w = 0.03f;

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

		if (!coin->GetIsEnd())
		{
			continue;
		}

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
		else if (i + 1 == clearCoins_.size())
		{
			isComplete_ = true;
			const int32_t countMax = 0;
			auto& emit = splashParticle_->GetEmitter()[useEmitterIndex_];
			emit.GetControlParam()[useEmitterIndex_].useFlag_ = false;
			emit.GetEmitParam()[useEmitterIndex_].count = countMax;
			emit.GetEmitParam()[useEmitterIndex_].translate = GameObjectManager::GetInstance()->GetObj3dData(coin->GetName())->GetWorldTransform().transform.translate;

		}

	}

	splashParticle_->Emit();
	splashParticle_->Update();
}

void ClearCoinManager::ParticleDraw()
{
	splashParticle_->Draw();
}

void ClearCoinManager::ImGuiUpdate()
{
	splashParticle_->ImGuiUpdate();
}

void ClearCoinManager::CreateCoinGameObject(const Math::Vector::Vector3& pos, int32_t index)
{
	//オブジェクトの作成
	const float kScale = 0.5f;
	Engine::Transform::TransformEular transform = { .scale{kScale,kScale,kScale},.rotate{} };
	const Math::Vector::Vector3 offset = { 0.0f,4.0f,-2.0f };
	transform.translate = offset;

	const float posX = 2.0f;
	if (index == static_cast<int>(CoinDirection::Left))
	{
		transform.translate.x = -posX;
	}
	if (index == static_cast<int>(CoinDirection::Rigft))
	{
		transform.translate.x = posX;
	}

	string coinName = "Coin";
	string auraName = "CoinAura";
	string name_num = coinName + to_string(index);

	for (size_t i = 0; i < 1; i++)
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
			const Math::Vector::Vector4 color = { 0.0f, 0.0f, 0.0f, 0.5f };
			data->SetIsDraw(true);
			data->GetDesc().colorDesc.color_ = color;
		}
		else
		{
			data->GetDesc().colorDesc.color_ = ColorConverter::ColorConversion(0xf0d64dff);
		}
		data->ChangePipline(make_unique<Phong3dSkinningPiplineDepthNoneWriteCommand>());
		GameObjectManager::GetInstance()->PushObj3dData(data, name_num);
	}

	name_num = coinName + to_string(index);

	unique_ptr<ClearCoin>coin = make_unique<ClearCoin>();
	coin->SetName(name_num);

	if (index <= coinCount_ - 1)
	{
		coin->SetCoinUse(CoinUse::Active);
	}
	else
	{
		coin->SetCoinUse(CoinUse::Inactive);
	}

	coin->Initialize();
	pos;
	clearCoins_[index] = move(coin);
}
