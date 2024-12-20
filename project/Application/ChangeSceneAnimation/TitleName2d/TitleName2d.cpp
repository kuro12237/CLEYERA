#include "TitleName2d.h"

void TitleName2d::Initialize(uint32_t noiseTex)
{
	name_ = "titleName";
	this->CreateJsonData("Utility/");
	this->CreateObject();
	this->CreateJsonSpriteData();

	///Jsonに追加
	AddJsonItem("dissolveMaskMax", dissolveMaskMax_);
	dissolveMaskMax_ = this->GetJsonItem<float>("dissolveMaskMax");
	AddJsonItem("dissolveEdgeColor", edgeColor_);
	edgeColor_ = this->GetJsonItem<Math::Vector::Vector4>("dissolveEdgeColor");
	AddJsonItem("dissolveEdgeMinMax", edgeMinMax_);
	edgeMinMax_ = this->GetJsonItem<Math::Vector::Vector2>("dissolveEdgeMinMax");

	//固有設定
	sprite_->SetNoiseTex(noiseTex);
	sprite_->SetSpriteMode(DissolveNone);

	sprite_->GetDissolveMask() = dissolveMaskMax_;
	sprite_->GetDissolveEdgeMinMax() = edgeMinMax_;
	sprite_->GetDissolveDdgeColor() = edgeColor_;

	this->CalcAnkerPos();
}

void TitleName2d::Update()
{

	this->CalcAnkerPos();
	///Dissolveの処理代入
	sprite_->GetDissolveMask() = *p_dissolveMask_;

	worldTransform_.UpdateMatrix();
}

void TitleName2d::ImGuiUpdate()
{
	string label = name_ + "LoadData";
	if (ImGui::Button(label.c_str()))
	{
		this->UpdateData();
		edgeColor_ = this->GetJsonItem<Math::Vector::Vector4>("dissolveEdgeColor");
		edgeMinMax_ = this->GetJsonItem<Math::Vector::Vector2>("dissolveEdgeMinMax");
	}

}
