#include "Warp.h"

void Warp::Initlaize(uint32_t index)
{
	///ゲートの初期化///番号を入れる
	warpGate_ = make_shared<WarpGate>();
	warpGate_->SetIndex(index);
	warpGate_->Initialize();

	string railFileName = warpGate_->GetRailDataFilePath();

	warpRute_ = make_unique<WarpRuate>();
	warpRute_->Initialize(railFileName);

	p_RailData_ = warpRute_->GetRailData();

	line_ = make_unique<Primitive::LineModel>();

	line_->Create(railFileName, uint32_t(p_RailData_.size * 2)
	);
	line_->resize(p_RailData_.size * 2);

	for (size_t i = 0; i < p_RailData_.size-1; i++)
	{
		line_->SetVec(p_RailData_.data[i].GetWorldPosition(),p_RailData_.data[i+1].GetWorldPosition(),i*2);
	}

	railPointGameObject_ = make_unique<Engine::Objects::Game3dObject>();
	railPointGameObject_->Create(make_unique<Phong3dPipline>());
	railPointGameObject_->SetModel(Engine::Manager::ModelManager::LoadObjectFile("DfCube"));
	railPointGameObject_->SetDesc(gameObjectDesc_);

}

void Warp::ImGuiUpdate()
{
	warpRute_->ImGuiUpdate();
}

void Warp::Update()
{
	warpRute_->Update();

}

void Warp::DebugDrawLine()
{
	warpRute_->Draw();
	line_->Draw();
	for (size_t i = 0; i < p_RailData_.size; i++)
	{
		railPointGameObject_->Draw(p_RailData_.data[i]);

	}
}
