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
	shared_ptr<Game3dObjectData> data = make_shared<Game3dObjectData>();
	data->SetObjectType("MESH");
	data->SetObjName(name_);
	data->SetModelHandle(modelHandle);
	data->Initialize({ {1.0f,1.0f,1.0f},{ } , {} }, { }, modelHandle);

	GameObjectManager::GetInstance()->PushObj3dData(data, name_);

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
	const float degree = 90.0f;
	auto playerCore = player_.lock();
	Math::Vector::Vector3 playerRotate = gameObjectManager_->GetObj3dData("Player")->GetWorldTransform().transform.rotate;

	if (playerCore->IsInState<PlayerStateAim>())
	{
		Move();
	}
	else
	{
		if (playerRotate.y >= Math::Vector::degreesToRadians(degree))
		{
			// レティクルの位置を計算
			reticlePos_.x = kRetickeRad_ * 1.0f;
			reticlePos_.y = 0.0f;
		}
		if (playerRotate.y<= -Math::Vector::degreesToRadians(degree))
		{
			// レティクルの位置を計算
			reticlePos_.x = kRetickeRad_ * -1.0f;
			reticlePos_.y = 0.0f;
		}
	}

	//Get
	Math::Matrix::Matrix4x4 viewMat = CameraManager::GetInstance()->GetCameraData()->matView_;
	Math::Matrix::Matrix4x4 ProjMat = CameraManager::GetInstance()->GetCameraData()->matProj_;

	const float offset = 1.5f;
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform();
	Math::Vector::Vector3 playerPos = GameObjectManager::GetInstance()->GetObj3dData("Player")->GetWorldTransform().GetWorldPosition();
	playerPos.y += offset;

	Math::Vector::Vector3 pos = { playerPos.x + reticlePos_.x,playerPos.y + reticlePos_.y,playerPos.z };
	interTarget_ = Math::Vector::Lerp(interTarget_, pos, lerpFlame_);

	transform.transform.translate = interTarget_;

	Math::Vector::Vector3 worldPos = transform.GetWorldPosition();
	Math::Vector::Vector3 p_r_Nlerp = Math::Vector::Normalize(Math::Vector::Subtruct(playerPos, transform.transform.translate));
	Math::Vector::Vector3 rotate = {};

	float rotateXZ = sqrt(pow(p_r_Nlerp.x, 2.0f) + pow(p_r_Nlerp.z, 2.0f));
	float height = -p_r_Nlerp.y;

	if (rotateXZ != 0.0f) {
		rotate.y = std::acos(p_r_Nlerp.z / rotateXZ);
		if (p_r_Nlerp.x < 0) {
			rotate.y = -rotate.y;
		}
	}
	else {
		rotate.y = 0.0f;
	}
	rotate.x = std::asin(height / sqrt(pow(height, 2.0f) + pow(rotateXZ, 2.0f)));
	transform.transform.rotate = rotate;

	//行列変換
	Math::Matrix::Matrix4x4 matViewport = Math::Matrix::ViewportMatrix(0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0, 1);
	Math::Matrix::Matrix4x4 matViewProjViewPort = Math::Matrix::Multiply(viewMat, Math::Matrix::Multiply(ProjMat, matViewport));

	worldTransform_.transform.translate = Math::Vector::TransformByMatrix(transform.transform.translate, matViewProjViewPort);
	worldTransform_.UpdateMatrix();
}

void PlayerReticle::Draw2d()
{
	sprite_->Draw(worldTransform_);
}

void PlayerReticle::Move()
{
	Math::Vector::Vector2 Rjoy = Engine::Input::GetInstance()->GetJoyRStickPos();
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
