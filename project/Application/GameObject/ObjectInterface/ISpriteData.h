#pragma once
#include"Sprite/Sprite.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/GlobalVariables/GlobalVariables.h"

/// <summary>
/// 2dのSpriteの抽象クラス
/// </summary>
class ISpriteData
{
public:
	ISpriteData();
	virtual ~ISpriteData() {};

	/// <summary>
	/// ImGui更新抽象
	/// </summary>
	virtual void ImGuiUpdate() {};

	/// <summary>
	/// Json枠を作成
	/// </summary>
	void CreateJsonData(const string& directoryPath = "");

	/// <summary>
	/// 項目を登録
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

#pragma region Get
	Engine::Transform::WorldTransform& GetWorldTransform() { return worldTransform_; }
	uint32_t GetTexHandle() { return texHandle_; }
	Engine::Objects::Sprite* GetSpriteData() { return sprite_.get(); }
	string GetName() { return name_; }
#pragma endregion

#pragma region Set
	void SetTexHandle(const uint32_t texHandle);
	void SetTransform(const Engine::Transform::TransformEular& transform) { worldTransform_.transform = transform; }
#pragma endregion


private:

	string prevFileName_ = "";

protected:

	/// <summary>
	/// 本体の作成
	/// </summary>
	void CreateObject();

	/// <summary>
	/// パラメーターの更新
	/// </summary>
	void UpdateData();

	void UpdateTextureData();

	string name_ = "";

	GlobalVariables* globalVariables_ = nullptr;
	GameObjectManager* gameObjectManager_ = nullptr;

	unique_ptr<Engine::Objects::Sprite>sprite_ = nullptr;
	Engine::Transform::WorldTransform worldTransform_ = {};
	string fileName_ = "";

	uint32_t texHandle_ = 0;
	Math::Vector::Vector2 ankerPos_ = {};
};
