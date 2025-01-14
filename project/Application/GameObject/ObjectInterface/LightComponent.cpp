#include "LightComponent.h"

void LightComponent::Update()
{
	pointLight_.position = this->GetJsonItem<Math::Vector::Vector3>("pos");
	pointLight_.decay = this->GetJsonItem<float>("decay");
	pointLight_.intencity = this->GetJsonItem<float>("intencity");
	pointLight_.radious = this->GetJsonItem<float>("radious");
	pointLight_.color = this->GetJsonItem<Math::Vector::Vector4>("color");

	lightManager_->AddList(pointLight_);
}

void LightComponent::CreateLightData()
{
	CreateJsonData();
	this->AddJsonItem("pos", pointLight_.position);
	this->AddJsonItem("decay", pointLight_.decay);
	this->AddJsonItem("intencity", pointLight_.intencity);
	this->AddJsonItem("radious", pointLight_.radious);
	this->AddJsonItem("color", pointLight_.color);

	pointLight_.position = this->GetJsonItem<Math::Vector::Vector3>("pos");
	pointLight_.decay = this->GetJsonItem<float>("decay");
	pointLight_.intencity = this->GetJsonItem<float>("intencity");
	pointLight_.radious = this->GetJsonItem<float>("radious");
	pointLight_.color = this->GetJsonItem<Math::Vector::Vector4>("color");

}
