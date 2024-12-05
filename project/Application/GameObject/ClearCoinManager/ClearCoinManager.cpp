#include "ClearCoinManager.h"

void ClearCoinManager::Initilaize()
{
	modelHandle_ = Engine::Manager::ModelManager::LoadGltfFile("StageCoin");
	auraModelHandle_ = Engine::Manager::ModelManager::LoadObjectFile("StageCoinAura");
	const float sizeMax = 3;
	clearCoins_.resize(sizeMax);

	for (int32_t index = 0; index < coinsMax_; index++)
	{
		this->CreateCoinGameObject({}, index);
	}

	splashParticle_ = make_unique<ClearCoinSplashParticle>();
	splashParticle_->Initialize();

	///パーティクルエディターを作る一旦そのまま
	auto& emit = splashParticle_->GetEmitter()[0];
	auto& control = emit.GetControlParam();
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


		if (coin->GetIsEnd())
		{
			// 現在のコインが終了した際の処理
			if (i + 1 < clearCoins_.size())
			{
				// 次のコインにアクセス
				unique_ptr<ClearCoin>& nextCoin = clearCoins_[i + 1];
				if (!nextCoin->GetIsStateAnimation())
				{
					const int32_t countMax = 3;
					auto& emit = splashParticle_->GetEmitter()[useEmitterIndex_];
					emit.GetControlParam()[useEmitterIndex_].useFlag_ = true;
					emit.GetEmitParam()[useEmitterIndex_].count = countMax;
					emit.GetEmitParam()[useEmitterIndex_].translate = GameObjectManager::GetInstance()->GetObj3dData(coin->GetName())->GetWorldTransform().transform.translate;

					nextCoin->StartAnimation(true);
					nextCoin->CreateState();
				}
				else
				{
					isComplete_ = true;
				}
			}
			else if (i + 1 == clearCoins_.size())
			{
				isComplete_ = true;
			}
		}
	}

	auto& emit = splashParticle_->GetEmitter()[useEmitterIndex_];
	if (emit.GetControlParam()[useEmitterIndex_].useFlag_)
	{
		const float particleEmitAddFlame = 1.0f / 10.0f;
		particleEmitFlame_ += particleEmitAddFlame;

		if (particleEmitFlame_ >= particleEmitMax_)
		{
			particleEmitFlame_ = 0.0f;
			emit.GetEmitParam()[useEmitterIndex_].count = 0;
			emit.GetControlParam()[useEmitterIndex_].useFlag_ = false;
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

		//オーラ
		string auraName_num=auraName+ to_string(index + i * 3);
		shared_ptr<Game3dObjectData> dataAura = make_shared<Game3dObjectData>();
		dataAura->SetObjectType("MESH");
		dataAura->SetIsDraw(false);
		dataAura->SetObjName(auraName_num);
		dataAura->SetModelFilePath("StageCoinAura");
		dataAura->Initialize(transform, {}, auraModelHandle_);
		if (i >= 1)
		{
			const Math::Vector::Vector4 color = { 0.0f, 0.0f, 0.0f, 0.5f };

			dataAura->SetIsDraw(true);
			dataAura->GetDesc().colorDesc.color_ = color;
		}
		else
		{
			dataAura->GetDesc().colorDesc.color_ = ColorConverter::ColorConversion(0xf0d64dff);
		}
		dataAura->ChangePipline(make_unique<Phong3dDissolvePiplineRasterFrontBackWriteCommand>());
		GameObjectManager::GetInstance()->PushObj3dData(dataAura, auraName_num);
		GameObjectManager::GetInstance()->SetNormalObjectParent(name_num, auraName_num);
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
