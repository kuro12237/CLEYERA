#include "GameScene.h"
#include<DirectXMath.h>

void GameScene::Initialize()
{
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.5f,-8.0f };
	testViewProjection_.Initialize();
	testViewProjection_.translation_ = { 0.0f,0.5f,-16.0f };

	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize("GameScene");

	worldTransform_.Initialize();
	worldTransform_.translate.y = 0.5f;
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	//ModelManager::ModelLoadNormalMap();
	//ModelManager::ModelUseSubsurface();
	//normalMonkeyHandle_= ModelManager::LoadObjectFile("TestMonkey");
	gameObject_->SetIsIndexDraw(true);
	normalMonkeyHandle_ = ModelManager::LoadGltfFile("Walk");

	AnimationManager::GetInstance()->LoadAnimation("SimpleSkin");
	//ModelManager::ModelUseSubsurface();
	smoothMonkeyHandle_ = ModelManager::LoadObjectFile("SmoothTestMonkey");
	gameObject_->SetModel(normalMonkeyHandle_);
	
	light_.position.y = 1.0f;
	light_.position.z = -1.0f;
	light_.radious = 10.0f;

	testLight.position.y = 1.0f;
	testLight.position.z = 4.0f;
	testLight.radious = 4.0f;
	testLight.color = { 1,0,0,1 };

	gameObject_->UseLight(true);
	gameObject_->SetlectModelPipeline(UE4_BRDF);

	ModelManager::ModelLoadNormalMap();
	uint32_t modelHandle = ModelManager::LoadObjectFile("TestGround");
	testGroundWorldTransform_.Initialize();
	testGroundGameObject_ = make_unique<Game3dObject>();
	testGroundGameObject_->Create();
	testGroundGameObject_->SetModel(modelHandle);
	testGroundGameObject_->UseLight(true);
	testGroundGameObject_->SetlectModelPipeline(PHONG_NORMAL_MODEL);
	testGroundGameObject_->SetIsIndexDraw(true);

	TestSkyDomeWorldTreanform_.Initialize();
	TestSkyDomeWorldTreanform_.scale = { 8.0f,8.0f,8.0f };
	//ModelManager::ModelLoadNormalMap();
	modelHandle = ModelManager::LoadObjectFile("TestSkyDome");
	testSkyDomeGameObject_= make_unique<Game3dObject>();
	testSkyDomeGameObject_->Create();
	testSkyDomeGameObject_->SetModel(modelHandle);
	testSkyDomeGameObject_->UseLight(true);
	testSkyDomeGameObject_->SetlectModelPipeline(PHONG_NORMAL_MODEL);

	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();

	defferedShading = make_unique<DefferredShading>();
	defferedShading->Initialize();

	DirectionalLight::Initialize();
}

void GameScene::Update(GameManager* Scene)
{
	debugCamera_->ImGuiUpdate();

	if (ImGui::TreeNode("Light"))
	{
		ImGui::DragFloat3("translate", &light_.position.x,-0.1f,0.1f);
		ImGui::DragFloat("decay", &light_.decay, -0.1f, 0.1f);
		ImGui::DragFloat("radious", &light_.radious, -0.1f, 0.1f);
		ImGui::DragFloat("intencity", &light_.intencity, -0.1f, 0.1f);
		ImGui::ColorPicker4("color", &light_.color.x);
		ImGui::TreePop();
	}


	gameObject_->SetlectModelPipeline(modelPipline_);


	light_.UpdateMatrix();
	LightingManager::AddList(light_);
	

	ImGui::Checkbox("TestRedLight", &UseTestRedLight_);
	if (UseTestRedLight_)
	{
		LightingManager::AddList(testLight);
	}

	postEffect_->Update();

	Move();

	//worldTransform_.rotation.y += 0.01f;
	worldTransform_.UpdateMatrix();
	testGroundWorldTransform_.UpdateMatrix();
	TestSkyDomeWorldTreanform_.UpdateMatrix();
	
	viewProjection_.UpdateMatrix();

	debugCamera_->Update();
	viewProjection_ = debugCamera_->GetData(viewProjection_);

	animationTimer_ += 1.0f / 60.0f;
	//TestAnimation();
	SAnimation::Skeleton skeleton = ModelManager::GetObjData(normalMonkeyHandle_).node.skeleton;
	SAnimation::Animation animation = AnimationManager::GetInstance()->GetData("SimpleSkin");
	AnimationManager::GetInstance()->ApplyAnimation(skeleton, animation, animationTimer_);

	if (Input::PushKeyPressed(DIK_N))
	{
		Scene->ChangeState(new TestScene);
		return;
	}
}

void GameScene::PostProcessDraw()
{
	postEffect_->PreDraw();
	gameObject_->Draw(worldTransform_, viewProjection_);
	testSkyDomeGameObject_->Draw(TestSkyDomeWorldTreanform_, viewProjection_);
	testGroundGameObject_->Draw(testGroundWorldTransform_, viewProjection_);

	postEffect_->PostDraw();
//color
//	defferedShading->PreColorDraw();
//	
//	gameObject_->ColorDraw(worldTransform_, viewProjection_);
//	testSkyDomeGameObject_->ColorDraw(TestSkyDomeWorldTreanform_, viewProjection_);
//	testGroundGameObject_->ColorDraw(testGroundWorldTransform_, viewProjection_);
//
//	defferedShading->PostColorDraw();
//
//	defferedShading->PreNormalDraw();
//	//normal
//	gameObject_->NormalDraw(worldTransform_, viewProjection_);
//	testSkyDomeGameObject_->NormalDraw(TestSkyDomeWorldTreanform_, viewProjection_);
//    testGroundGameObject_->NormalDraw(testGroundWorldTransform_, viewProjection_);
//
//	defferedShading->PostNormalDraw();
//    //pos
//	defferedShading->PrePosDraw();
//
//	gameObject_->PosDraw(worldTransform_, viewProjection_);
//	testSkyDomeGameObject_->PosDraw(TestSkyDomeWorldTreanform_, viewProjection_);
//	testGroundGameObject_->PosDraw(testGroundWorldTransform_, viewProjection_);
//
//	defferedShading->PostPosDraw();
////depth
//	defferedShading->PreDepthDraw();
//
//	gameObject_->ColorDraw(worldTransform_, viewProjection_);
//	testSkyDomeGameObject_->ColorDraw(TestSkyDomeWorldTreanform_, viewProjection_);
//	testGroundGameObject_->ColorDraw(testGroundWorldTransform_, viewProjection_);
//
//	defferedShading->PostDepthDraw();
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	postEffect_->Draw(viewProjection_);
	//defferedShading->Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}

void GameScene::Move()
{

	const float speed = 0.1f;
	if (Input::PushKey(DIK_W))
	{
		worldTransform_.translate.z += speed;
	}
	if (Input::PushKey(DIK_S))
	{
		worldTransform_.translate.z -= speed;
	}
	if (Input::PushKey(DIK_A))
	{
		worldTransform_.translate.x -= speed;
	}if (Input::PushKey(DIK_D))
	{
		worldTransform_.translate.x += speed;
	}
}

void GameScene::TestAnimation()
{
	SAnimation::Animation data = AnimationManager::GetInstance()->GetData("AnimatedCube");
	animationTimer_ += 1.0f / 60.0f;
	animationTimer_ = std::fmod(animationTimer_, data.duration);
	SAnimation::NodeAnimation& rootNodeAnimation = data.NodeAnimation["AnimatedCube"];
	Math::Vector::Vector3 translate = AnimationManager::CalculateValue(rootNodeAnimation.translate.keyframes, animationTimer_);
	Math::Qua::Quaternion quaternion = AnimationManager::CalculateValue(rootNodeAnimation.rotate.keyframes, animationTimer_);
	Math::Vector::Vector3 scale = AnimationManager::CalculateValue(rootNodeAnimation.scale.keyframes, animationTimer_);

	Math::Matrix::Matrix4x4 tm = Math::Matrix::TranslateMatrix(translate);
	Math::Matrix::Matrix4x4 rm = Math::Qua::RotateMatrix(quaternion);
	Math::Matrix::Matrix4x4 sm = Math::Matrix::ScaleMatrix(scale);
	Math::Matrix::Matrix4x4 localMat = Math::Matrix::Multiply(sm, Math::Matrix::Multiply(rm, tm));
	worldTransform_.matWorld = Math::Matrix::Multiply(worldTransform_.matWorld, localMat);
	worldTransform_.TransfarMatrix();

}
