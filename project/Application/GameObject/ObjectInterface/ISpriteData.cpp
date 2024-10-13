#include "ISpriteData.h"

ISpriteData::ISpriteData()
{
	globalVariables_ = GlobalVariables::GetInstance();
}

void ISpriteData::CreateJsonData()
{
	globalVariables_->CreateGroup(name_);
}

void ISpriteData::CreateJsonSpriteData()
{
	AddJsonItem("transform", worldTransform_.transform);
	worldTransform_.transform = GetJsonItem<TransformEular>("transform");
	AddJsonItem("fileName", fileName_);
	fileName_ = GetJsonItem<string>("fileName");

	//�t�@�C���̖��O����������ǂݍ���
	if (fileName_ != "")
	{
		texHandle_ = TextureManager::LoadPngTexture(fileName_);
		sprite_->SetTexHandle(texHandle_);
	}

	AddJsonItem("ankerPos", ankerPos_);
	ankerPos_ = GetJsonItem<Math::Vector::Vector2>("ankerPos");
}

void ISpriteData::CreateObject()
{
	sprite_ = make_unique<Sprite>();

	
	sprite_->Initialize();
	sprite_->SetTexHandle(texHandle_);
	prevFileName_ = fileName_;

	worldTransform_.Initialize();
}

void ISpriteData::UpdateData()
{
	worldTransform_.transform = GetJsonItem<TransformEular>("transform");
	fileName_ = GetJsonItem<string>("fileName");
	ankerPos_ = GetJsonItem<Math::Vector::Vector2>("ankerPos");
	Math::Vector::Vector2 texSize = TextureManager::GetTextureSize(texHandle_);

	//�A���J�[�v�Z
	ankerPos_.x = texSize.x * -ankerPos_.x;
	ankerPos_.y = texSize.y * -ankerPos_.y;
	sprite_->GetPos() = ankerPos_;

	//�t�@�C�������O�t���[���ƈ������ēǂݍ���
	if (prevFileName_ != fileName_)
	{
		texHandle_ = TextureManager::LoadPngTexture(fileName_);
		sprite_->SetTexHandle(texHandle_);
	}

	prevFileName_ = fileName_;

}

void ISpriteData::Draw2d()
{
	sprite_->Draw(worldTransform_);
}

void ISpriteData::CalcAnkerPos()
{
	Math::Vector::Vector2 texSize = TextureManager::GetTextureSize(texHandle_);

	//�A���J�[�v�Z
	sprite_->GetPos().x = texSize.x * -ankerPos_.x;
	sprite_->GetPos().y = texSize.y * -ankerPos_.y;
}
