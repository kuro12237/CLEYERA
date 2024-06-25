#include "PlayerReticle.h"

void PlayerReticle::Initialize()
{
	name_ = "PlayerReticle";

	Game3dObjectData data;
	data.gameObject = make_unique<Game3dObject>();
	data.gameObject->Create();
	data.gameObject->SetModel(ModelManager::LoadObjectFile("DfCube"));
	data.worldTransform.Initialize();
	GameObjectManager::GetInstance()->PushObj3dData(data, name_);
	GameObjectManager::GetInstance()->SetParent("Player", "PlayerReticle");
	transform_.scale = { 1.0f,1.0f,1.0f };
}

void PlayerReticle::ImGuiUpdate()
{
	Math::Vector::Vector3 p = GameObjectManager::GetInstance()->GetObj3dData(name_).worldTransform.GetWorldPosition();
	ImGui::DragFloat3("t", &p.x);
}

void PlayerReticle::Update()
{

}

void PlayerReticle::Move()
{
	Math::Vector::Vector2 Rjoy = Input::GetInstance()->GetJoyRStickPos();

	Math::Vector::Vector2 normalizedRjoy = Math::Vector::Normalize(Rjoy);
	// レティクルの位置を計算
	Math::Vector::Vector2 reticlePos = {
		kRetickeRad_ * normalizedRjoy.x,
		kRetickeRad_ * normalizedRjoy.y
	};
	transform_.translate.x = reticlePos.x;
	transform_.translate.y = reticlePos.y;

}
