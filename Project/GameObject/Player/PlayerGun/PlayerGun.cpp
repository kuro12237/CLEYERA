#include "PlayerGun.h"

void PlayerGun::Initlalize()
{
	//model設定
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObjectDesc_.useLight = true;
	gameObject_->SetDesc(gameObjectDesc_);
	modelHandle_ = ModelManager::LoadObjectFile("PlayerGun");
	gameObject_->SetModel(modelHandle_);

	worldTransform_.Initialize();

	//状態
	StateInitialize();
}

void PlayerGun::Update()
{
	
	//弾消し
	bullets_.remove_if([](shared_ptr<PlayerGunBullet> b) {
		if (b->GetIsDeadFlag()) {
			b.reset();
			return true;
		}
		return false;
		});

	for (shared_ptr<PlayerGunBullet> b : bullets_)
	{
		b->Update();
	}

	bulletRate_ += 1.0f;

	prevStateno_ = currentStateNo_;
	currentStateNo_ = states_[currentStateNo_]->GetstateNo();
	if (prevStateno_ != currentStateNo_)
	{
		states_[currentStateNo_]->Initialize();
	}

	states_[currentStateNo_]->Update(this);

	worldTransform_.UpdateMatrix();
}

void PlayerGun::Animation()
{
}

void PlayerGun::Draw(const CameraData& camera)
{
	gameObject_->Draw(worldTransform_,camera);

	for (shared_ptr<PlayerGunBullet> b : bullets_)
	{
		b->Draw(camera);
	}
}

void PlayerGun::ImGuiUpdate()
{
	ImGui::Begin("test");
	ImGui::Text("Bulletcount %d", bulletCount_);
	ImGui::End();
}

void PlayerGun::Attack()
{
	if (bulletCount_ < bulletCountMax_)
	{
		if (bulletRate_ >= bulletRateMax_)
		{
			const Math::Vector::Vector2 randomSize = { -1.0f,1.0f };
			Math::Vector::Vector3 randomPos = {
				RandomGenerator::GetInstance()->GetFloat(randomSize.x, randomSize.y),
				RandomGenerator::GetInstance()->GetFloat(randomSize.x, randomSize.y),
				0.0f
			};
			reticlePos = Math::Vector::Add(reticlePos, randomPos);

			Math::Vector::Vector3 prSubtruct = Math::Vector::Subtruct(reticlePos, worldTransform_.GetWorldPosition());
			Math::Vector::Vector3 Nvelocity = Math::Vector::Normalize(prSubtruct);
			const float speed = 0.5f;
			Math::Vector::Vector3 velocity = Math::Vector::Multiply(Nvelocity, speed);

			shared_ptr<PlayerGunBullet>b = make_shared<PlayerGunBullet>();
			b->Initalize(worldTransform_.GetWorldPosition(), velocity);

			bullets_.push_back(b);
			bulletCount_++;
			bulletRate_ = 0.0f;
		}
	}
}

void PlayerGun::StateInitialize()
{
	states_[STAND] = make_unique<PlayerGunStandState>();
	states_[ATTACK] = make_unique<PlayerGunAttackState>();
	states_[RELOAD] = make_unique<PlayerGunReloadState>();

	currentStateNo_ = STAND;
	states_[currentStateNo_]->Initialize();
};