#include "WarpRuate.h"

void WarpRuate::Initialize(const string& fileName)
{
	railData_ = RailLoader::LoadRail(fileName);
	splineMotion_ = make_unique<SplineMotion>();
	splineMotion_->SetP_RailData(railData_);


	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create(make_unique<Phong3dPipline>());
	gameObject_->SetModel(ModelManager::LoadObjectFile("DfCube"));

	worldTransform_.Initialize();
}

void WarpRuate::ImGuiUpdate()
{
	ImGui::Checkbox("motionFlag", &isStart_);
	splineMotion_->SetIsStartFlag(isStart_);
}

void WarpRuate::Update()
{
	splineMotion_->UpdateParamerter(kFlame_);
	worldTransform_.transform.translate = splineMotion_->CatmullRomInterpolation();
	worldTransform_.UpdateMatrix();

}

void WarpRuate::Draw()
{
	gameObject_->Draw(worldTransform_);
}
