#include "PlayerGun.h"

void PlayerGun::Initlalize()
{
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObjectDesc_.useLight = true;
	gameObject_->SetDesc(gameObjectDesc_);
	modelHandle_ = ModelManager::LoadObjectFile("PlayerGun");
	gameObject_->SetModel(modelHandle_);

	worldTransform_.Initialize();
	worldTransform_.translate.z = -3.0f;
}

void PlayerGun::Update()
{
	
	if (Input::PushBottonPressed(XINPUT_GAMEPAD_B))
	{
		Attack();
	}

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
	//ImGui::DragFloat3("velo", &Nvelocity.x);
	ImGui::End();
}

void PlayerGun::Attack()
{
	Math::Vector::Vector3 prSubtruct = Math::Vector::Subtruct(reticlePos, worldTransform_.GetWorldPosition());
	Math::Vector::Vector3 Nvelocity = Math::Vector::Normalize(prSubtruct);

	shared_ptr<PlayerGunBullet>b = make_shared<PlayerGunBullet>();
	b->Initalize(worldTransform_.GetWorldPosition(),Nvelocity);

	bullets_.push_back(b);

};