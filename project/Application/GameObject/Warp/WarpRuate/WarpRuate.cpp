#include "WarpRuate.h"

void WarpRuate::Initialize(const string& fileName)
{
	railData_ = RailLoader::LoadRail(fileName);
	splineMotion_ = make_unique<SplineMotion>();
	splineMotion_->SetP_RailData(railData_);

}

void WarpRuate::ImGuiUpdate()
{
}

void WarpRuate::Update()
{

}

void WarpRuate::Draw()
{
}
