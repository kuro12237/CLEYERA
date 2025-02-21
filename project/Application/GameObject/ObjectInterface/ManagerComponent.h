#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/convert/convert.h"
#include"IObjectData.h"

/// <summary>
/// マネージャーリスト抽象クラス
/// </summary>
class ManagerComponent:public JsonComponent
{
public:
	ManagerComponent() { gameObjectManager_ = GameObjectManager::GetInstance();};
	virtual ~ManagerComponent() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="data"></param>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// ImGui更新
	/// </summary>
	virtual void ImGuiUpdate() {};

	void ImGuiBegin(string tag) { ImGui::Begin(tag.c_str()); };
	void ImGuiEnd() { ImGui::End(); }

	/// <summary>
	/// 空か確認空だった場合削除
	/// </summary>
	void RemoveEmptyObjList();

private:

protected:

	GameObjectManager* gameObjectManager_ = nullptr;
	list<weak_ptr<IObjectData>>objDataList_;
	size_t countMax_ = 0;

};