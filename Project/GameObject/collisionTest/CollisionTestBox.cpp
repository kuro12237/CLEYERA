#include "CollisionTestBox.h"

void CollisionTestBox::Initialize()
{
	SetName("CollisionTestBox");
	SetObjectData(this->transform_);

	id_ = kNormalBlock;

	shared_ptr<Game3dObjectData> data;
	data = make_shared<Game3dObjectData>();

	data->Initialize(transform_, {}, ModelManager::LoadObjectFile("DfCube"));
	transform_.scale = { 1.0f,1.0f,1.0f };
	transform_.translate = { 2.0f,4.0f,0.0f };


	GameObjectManager::GetInstance()->PushObj3dData(data, name_);
}

void CollisionTestBox::ImGuiUpdate()
{
	ImGui::DragFloat3("min", &aabb_.min.x,0.1f,-0.1f);

	ImGui::DragFloat3("max", &aabb_.max.x, 0.1f, -0.1f);
}

void CollisionTestBox::Update()
{
	


}

void CollisionTestBox::OnCollision(ICollider* c)
{
	c;
}
