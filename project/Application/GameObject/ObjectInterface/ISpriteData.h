#pragma once
#include"Sprite/Sprite.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/GlobalVariables/GlobalVariables.h"

class ISpriteData
{
public:
	ISpriteData();
	virtual ~ISpriteData() {};

	virtual void ImGuiUpdate() = 0;

	/// <summary>
	/// Json枠を作成
	/// </summary>
	void CreateJsonData();

	/// <summary>
	/// ほぼン項目を登録
	/// </summary>
	template<typename T>
	void AddJsonItem(string itemName, T value) { return globalVariables_->AddItem(name_, itemName, value); }

	/// <summary>
	/// Jsonデータを入手
	/// </summary>
	template<typename T>
	T GetJsonItem(string itemName) { return globalVariables_->GetValue<T>(name_, itemName); }

	/// <summary>
	/// SpriteWorldTransformなどのデータをJson二作成
	/// </summary>
	void CreateJsonSpriteData();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw2d();

	/// <summary>
	/// アンカーを計算
	/// </summary>
	void CalcAnkerPos();

private:

	string prevFileName_ = "";

protected:
	void CreateObject();
	void UpdateData();

	string name_ = "";

	GlobalVariables* globalVariables_ = nullptr;
	GameObjectManager* gameObjectManager_ = nullptr;

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};
	string fileName_ = "";

	uint32_t texHandle_ = 0;
	Math::Vector::Vector2 ankerPos_ = {};
};
