#include "PlayerReticle.h"

using namespace Engine::Base::DX;
using namespace Engine::Base::Win;
using namespace Engine::Transform;
using namespace Engine::Objects;
using namespace Engine::Manager;

void PlayerReticle::Initialize()
{
	name_ = "PlayerReticle";
	uint32_t modelHandle = ModelManager::LoadObjectFile("DfCube");
	shared_ptr<Game3dObjectData> data;
	data = make_shared<Game3dObjectData>();
	data->SetObjName(name_);
	data->SetModelHandle(modelHandle);
	data->Initialize({}, {}, 0);

	GameObjectManager::GetInstance()->PushObj3dData(data, name_);
	//GameObjectManager::GetInstance()->SetParent("Player", name_);

	uint32_t texHandle = TextureManager::LoadPngTexture("Player/Reticle/Reticle.png");
	Math::Vector::Vector2 texPos = TextureManager::GetTextureSize(texHandle);
	texPos.x *= -0.5f;
	texPos.y *= -0.5f;
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(texPos);
	sprite_->SetTexHandle(texHandle);
	worldTransform_.Initialize();
	const float kScale = 0.05f;
	worldTransform_.transform.scale = { kScale,kScale,kScale };
}

void PlayerReticle::ImGuiUpdate()
{
	
}

void PlayerReticle::Update()
{
	//Get
	Math::Matrix::Matrix4x4 viewMat = CameraManager::GetInstance()->GetCameraData()->matView_;
	Math::Matrix::Matrix4x4 ProjMat = CameraManager::GetInstance()->GetCameraData()->matProj_;
	Math::Vector::Vector3 reticleWorldPos = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().GetWorldPosition();
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform;
	Math::Vector::Vector3 playerPos = GameObjectManager::GetInstance()->GetObj3dData("Player")->GetWorldTransform().GetWorldPosition();

	interTarget_ = Math::Vector::Lerp(interTarget_, Math::Vector::Vector3(reticlePos_.x, reticlePos_.y, 0.0f), 0.5f);
	reticleWorldPos = Math::Vector::Add(reticleWorldPos, interTarget_);
	transform.translate.x = playerPos.x;
	transform.translate.y = playerPos.y;

	transform.translate.x += reticlePos_.x;
	transform.translate.y += reticlePos_.y;
	transform.translate.z = 0.0f;
	transform.rotate = { 0.0f,0.0f,0.0f };
	//行列変換
	Math::Matrix::Matrix4x4 matViewport = Math::Matrix::ViewportMatrix(0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0, 1);
	Math::Matrix::Matrix4x4 matViewProjViewPort = Math::Matrix::Multiply(viewMat, Math::Matrix::Multiply(ProjMat, matViewport));

	worldTransform_.transform.translate =Math::Vector::TransformByMatrix(reticleWorldPos, matViewProjViewPort);
	worldTransform_.UpdateMatrix();
}

void PlayerReticle::Draw2d()
{
	sprite_->Draw(worldTransform_);
}

void PlayerReticle::Move()
{
	Math::Vector::Vector2 Rjoy = Input::GetInstance()->GetJoyRStickPos();
	Math::Vector::Vector2 normalizedRjoy_ = Math::Vector::Normalize(Rjoy);

	// レティクルの位置を計算
	reticlePos_ = {
		kRetickeRad_ * normalizedRjoy_.x,
		kRetickeRad_ * normalizedRjoy_.y
	};
}

Math::Vector::Vector3 PlayerReticle::NDCToScreen(const Math::Vector::Vector3& ndc, float screenWidth, float screenHeight)
{
	Math::Vector::Vector3 screenPos;
	screenPos.x = (ndc.x * 0.5f + 0.5f) * screenWidth;
	screenPos.y = (ndc.y * -0.5f + 0.5f) * screenHeight;
	screenPos.z = ndc.z; // 深度はそのまま
	return screenPos;
}
