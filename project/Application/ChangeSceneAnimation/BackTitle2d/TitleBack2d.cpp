#include "TitleBack2d.h"


void TitleBack2d::Initialize(uint32_t noiseTex)
{
	name_ = "titleBack";
	this->CreateJsonData("Utility/");
	this->CreateObject();
	this->CreateJsonSpriteData();

	///Json‚É’Ç‰Á
	AddJsonItem("dissolveMaskMax", dissolveMaskMax_);
	dissolveMaskMax_ = this->GetJsonItem<float>("dissolveMaskMax");
	AddJsonItem("dissolveEdgeColor", edgeColor_);
	edgeColor_ = this->GetJsonItem<Math::Vector::Vector4>("dissolveEdgeColor");
	AddJsonItem("dissolveEdgeMinMax", edgeMinMax_);
	edgeMinMax_ = this->GetJsonItem<Math::Vector::Vector2>("dissolveEdgeMinMax");

	//ŒÅ—LÝ’è
	sprite_->SetNoiseTex(noiseTex);
	sprite_->SetSpriteMode(DissolveNone);

	sprite_->GetDissolveMask() = dissolveMaskMax_;
	sprite_->GetDissolveEdgeMinMax() = edgeMinMax_;
	sprite_->GetDissolveDdgeColor() = edgeColor_;
}

void TitleBack2d::Update()
{
	this->CalcAnkerPos();
	///Dissolve‚Ìˆ—‘ã“ü
	sprite_->GetDissolveMask() = *p_dissolveMask_;

	worldTransform_.UpdateMatrix();
}

void TitleBack2d::ImGuiUpdate()
{
	string label = name_ + "LoadData";
	if (ImGui::Button(label.c_str()))
	{
		this->UpdateData();
		edgeColor_ = this->GetJsonItem<Math::Vector::Vector4>("dissolveEdgeColor");
		edgeMinMax_ = this->GetJsonItem<Math::Vector::Vector2>("dissolveEdgeMinMax");
	}
}
