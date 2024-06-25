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

	const float Speed = 0.1f;
	transform_.translate.x += Rjoy.x * Speed;
	transform_.translate.y += Rjoy.y * Speed;

}
