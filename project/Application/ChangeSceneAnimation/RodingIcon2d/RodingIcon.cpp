#include "RodingIcon.h"

using namespace Engine::Transform;

void RodingIcon2d::Initialize(uint32_t noiseTex)
{
	name_ = "rodingIcon";
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
	AddJsonItem("rotateSpeed", rotateSpeed_);
	rotateSpeed_ = this->GetJsonItem<float>("rotateSpeed");

	//ŒÅ—LÝ’è
	sprite_->SetNoiseTex(noiseTex);
	sprite_->SetSpriteMode(DissolveNone);

	sprite_->GetDissolveMask() = dissolveMaskMax_;
	sprite_->GetDissolveEdgeMinMax() = edgeMinMax_;
	sprite_->GetDissolveDdgeColor() = edgeColor_;

	this->CalcAnkerPos();
	worldTransform_.UpdateMatrix();
}

void RodingIcon2d::Update()
{
	this->CalcAnkerPos();
	
	worldTransform_.transform.rotate.z += rotateSpeed_;
	///Dissolve‚Ìˆ—‘ã“ü
	sprite_->GetDissolveMask() = *p_dissolveMask_;

	worldTransform_.UpdateMatrix();
}

void RodingIcon2d::ImGuiUpdate()
{
	string label = name_ + "LoadData";
	if (ImGui::Button(label.c_str()))
	{
		this->UpdateData();
		edgeColor_ = this->GetJsonItem<Math::Vector::Vector4>("dissolveEdgeColor");
		edgeMinMax_ = this->GetJsonItem<Math::Vector::Vector2>("dissolveEdgeMinMax");
	}
	worldTransform_.UpdateMatrix();
}
