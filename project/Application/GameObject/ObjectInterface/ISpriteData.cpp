#include "ISpriteData.h"

using namespace Engine::Objects;

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;


ISpriteData::ISpriteData()
{
	globalVariables_ = GlobalVariables::GetInstance();
}

void ISpriteData::CreateJsonData(const string& directoryPath)
{
	globalVariables_->CreateGroup(name_,directoryPath);
}

void ISpriteData::CreateJsonSpriteData()
{
	AddJsonItem("transform", worldTransform_.transform);
	worldTransform_.transform = GetJsonItem<TransformEular>("transform");
	AddJsonItem("fileName", fileName_);
	fileName_ = GetJsonItem<string>("fileName");

	//ファイルの名前があったら読み込む
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
}

void ISpriteData::UpdateTextureData()
{
	fileName_ = GetJsonItem<string>("fileName");
	ankerPos_ = GetJsonItem<Math::Vector::Vector2>("ankerPos");
	Math::Vector::Vector2 texSize = TextureManager::GetTextureSize(texHandle_);

	//アンカー計算
	sprite_->GetPos().x = texSize.x * -ankerPos_.x;
	sprite_->GetPos().y = texSize.y * -ankerPos_.y;

	//ファイル名が前フレームと違ったら再読み込み
	if (prevFileName_ != fileName_)
	{
		texHandle_ = TextureManager::LoadPngTexture(fileName_);
		sprite_->SetTexHandle(texHandle_);
	}

	prevFileName_ = fileName_;

}

void ISpriteData::Draw2d()
{
	if (sprite_)
	{
		sprite_->Draw(worldTransform_);
	}
}

void ISpriteData::CalcAnkerPos()
{
	Math::Vector::Vector2 texSize = TextureManager::GetTextureSize(texHandle_);

	//アンカー計算
	sprite_->GetPos().x = texSize.x * -ankerPos_.x;
	sprite_->GetPos().y = texSize.y * -ankerPos_.y;
}

void ISpriteData::SetTexHandle(const uint32_t texHandle)
{
	texHandle_ = texHandle;
	fileName_ = TextureManager::GetTexFilePath(texHandle_);
	sprite_->SetTexHandle(texHandle_);
}
