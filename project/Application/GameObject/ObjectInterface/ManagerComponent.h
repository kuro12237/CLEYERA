#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/convert/convert.h"


/// <summary>
/// マネージャーリスト抽象クラス
/// </summary>
class ManagerComponent
{
public:
	ManagerComponent() { gameObjectManager_ = GameObjectManager::GetInstance(); };
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

private:

	GameObjectManager* gameObjectManager_ = nullptr;

};