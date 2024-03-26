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
	normalMonkeyHandle_= ModelManager::LoadObjectFile("TestMonkey");
	normalMonkeyHandle_ = ModelManager::LoadObjectFile("Sphere");
	ModelManager::ModelUseSubsurface();
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
#ifdef _USE_IMGUI

	debugCamera_->ImGuiUpdate();

	if (ImGui::TreeNode("Light"))
	{
		ImGui::DragFloat3("translate", &light_.worldPos_.x,-0.1f,0.1f);
		ImGui::DragFloat("decay", &light_.decay, -0.1f, 0.1f);
		ImGui::DragFloat("radious", &light_.radious, -0.1f, 0.1f);
		ImGui::DragFloat("intencity", &light_.intencity, -0.1f, 0.1f);
		ImGui::ColorPicker4("color", &light_.color.x);
		ImGui::TreePop();
	}

	auto SelectPipline = [](ModelShaderSelect s)
	{
		switch (s)
		{
		case PHONG_MODEL:
			return "PHONG_MODEL";
		case UE4_BRDF:
			return"UE4_BRDF";
		case PHONG_NORMAL_MODEL:
			return "PHONG_NORMAL_MODEL";
		case PHONG_SUBSURFACE_MODEL:
			return "PHONG_SUBSURFACE_MODEL";
		default:
			return "UnKnown";
		}
	};


	if (ImGui::TreeNode("model"))
	{
		ImGui::Checkbox("SmoothMonkeyModel",&SmoothMoneyUseFlag_);
		if (SmoothMoneyUseFlag_)
		{
			gameObject_->SetModel(smoothMonkeyHandle_);
		}
		else {
			gameObject_->SetModel(normalMonkeyHandle_);
		}

		ImGui::DragFloat("absorptionCoefficient", &absorptionCoefficient_, -0.1f, 0.1f);
		ImGui::DragFloat("scatterCoefficient_", &scatterCoefficient_, -0.1f, 0.1f);
		ImGui::DragFloat("scatterDistance", &scatterDistance_, -0.1f, 0.1f);
		gameObject_->SetAbsorptionCoefficient(absorptionCoefficient_);
		gameObject_->SetScatterCoefficient(scatterCoefficient_);
		gameObject_->SetScatterDistance(scatterDistance_);

		ImGui::DragFloat3("translate", &worldTransform_.translate.x, -0.1f, 0.1f);

		if (ImGui::BeginCombo("Shading",SelectPipline(modelPipline_)))
		{
			for (int i = 0; i < 5; i++) {
				bool isSelected = (modelPipline_ == static_cast<ModelShaderSelect>(i));
				if (ImGui::Selectable(SelectPipline(static_cast<ModelShaderSelect>(i)), isSelected))
					modelPipline_ = static_cast<ModelShaderSelect>(i);
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::TreePop();
	}

	gameObject_->SetlectModelPipeline(modelPipline_);

	auto SetNamePostEffect = [](SelectPostEffect b)
	{
		switch (b)
		{
		case GRAYSCALE:
			return "GRAYSCALE";
		case INVERT:
				return "INVERT";

		default:
			return "unKnown";
		}
	};

	if (ImGui::TreeNode("postEffectParam"))
	{
		ImGui::DragFloat2("uvscale", &postEffectuvScale.x, -0.1f, 0.1f);
		ImGui::DragFloat("GrayFactor", &postEffectGrayFactor_, -0.01f, 0.01f);
		ImGui::DragFloat("invertFactor", &postEffectInvertFactor_, -0.01f, 0.01f);
		ImGui::DragFloat("bringhtness", &postEffectBringhtnessFactor_, -0.01f, 0.01f);
		ImGui::DragFloat("AverageIntensity", &postEffectAverageBlurIntensity_, -0.01f, 0.01f);
		ImGui::DragFloat("ContrastFactor", &postEffectContrastFactor_, -0.01f, 0.01f);
		ImGui::DragFloat("hueFactor", &postEffectHueFactor_, -0.01f, 0.01f);

		if (ImGui::BeginCombo("BlendChange", SetNamePostEffect(selectPostEffect_)))
		{
			for (int i = 0; i < 2; i++) {
				bool isSelected = (selectPostEffect_ == static_cast<SelectPostEffect>(i));
				if (ImGui::Selectable(SetNamePostEffect(static_cast<SelectPostEffect>(i)), isSelected))
					selectPostEffect_ = static_cast<SelectPostEffect>(i);
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::TreePop();
	}
#endif // _USE_IMGUI

	light_.UpdateMatrix();
	LightingManager::AddList(light_);
	

	ImGui::Checkbox("TestRedLight", &UseTestRedLight_);
	if (UseTestRedLight_)
	{
		LightingManager::AddList(testLight);
	}
	postEffect_->SetSelectPostEffect(GRAYSCALE,true);
	postEffect_->SetSelectPostEffect(INVERT, true);
	postEffect_->SetSelectPostEffect(BRINGHTNESS, true);
	postEffect_->SetSelectPostEffect(AVERAGE_BLUR, true);
	//postEffect_->SetSelectPostEffect(HUE, true);
	postEffect_->SetSelectPostEffect(CONTRAST, true);

	postEffect_->SetBringhtnessFactor(postEffectBringhtnessFactor_);
	postEffect_->SetGrayFactor(postEffectGrayFactor_);
	postEffect_->SetInvertFactor(postEffectInvertFactor_);
	postEffect_->SetBlurintensity(postEffectAverageBlurIntensity_);
	postEffect_->SetContrastFactor(postEffectContrastFactor_);
	postEffect_->SetHueFactor(postEffectHueFactor_);

	postEffect_->SetUvScale(postEffectuvScale);
	postEffect_->Update();

	Move();

	worldTransform_.rotation.y += 0.01f;
	worldTransform_.UpdateMatrix();
	testGroundWorldTransform_.UpdateMatrix();
	TestSkyDomeWorldTreanform_.UpdateMatrix();
	
	viewProjection_.UpdateMatrix();

	debugCamera_->Update();
	viewProjection_ = debugCamera_->GetData(viewProjection_);


	if (Input::PushKeyPressed(DIK_N))
	{
		Scene->ChangeState(new TestScene);
		return;
	}
}

void GameScene::PostProcessDraw()
{
	postEffect_->PreDraw();
	
	//testSkyDomeGameObject_->Draw(TestSkyDomeWorldTreanform_, viewProjection_);
	//testGroundGameObject_->Draw(testGroundWorldTransform_, viewProjection_);

	postEffect_->PostDraw();

	defferedShading->PreColorDraw();
	gameObject_->ColorDraw(worldTransform_, viewProjection_);
	//testGroundGameObject_->Draw(testGroundWorldTransform_, viewProjection_);
	testSkyDomeGameObject_->ColorDraw(TestSkyDomeWorldTreanform_, viewProjection_);
	testGroundGameObject_->ColorDraw(testGroundWorldTransform_, viewProjection_);

	defferedShading->PostColorDraw();

	defferedShading->PreNormalDraw();
	gameObject_->NormalDraw(worldTransform_, viewProjection_);
	testSkyDomeGameObject_->NormalDraw(TestSkyDomeWorldTreanform_, viewProjection_);
    testGroundGameObject_->NormalDraw(testGroundWorldTransform_, viewProjection_);

	defferedShading->PostNormalDraw();
	defferedShading->PreDepthDraw();
	gameObject_->ColorDraw(worldTransform_, viewProjection_);
	//testGroundGameObject_->Draw(testGroundWorldTransform_, viewProjection_);
	testSkyDomeGameObject_->ColorDraw(TestSkyDomeWorldTreanform_, viewProjection_);
	testGroundGameObject_->ColorDraw(testGroundWorldTransform_, viewProjection_);

	defferedShading->PostDepthDraw();
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	//postEffect_->Draw(viewProjection_);
	defferedShading->Draw(viewProjection_);
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
