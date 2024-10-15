#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"

/// <summary>
/// 重力処理を
/// </summary>
class GravityManager
{
public:
	GravityManager() {};
	~GravityManager() {};

	/// <summary>
	/// リスト削除
	/// </summary>
	void ClearList() { objectDatas_.clear(); }

	/// <summary>
	/// リスト登録
	/// </summary>
	/// <param name="data"></param>
	void PushList(IObjectData* data) { objectDatas_.push_back(data); }

	/// <summary>
	/// 重力処理
	/// </summary>
	void CheckGravity();

private:

	list<IObjectData*>objectDatas_;

	float gravity_ = 0.01f;

};

