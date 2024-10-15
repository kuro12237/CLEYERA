#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"

/// <summary>
/// �d�͏�����
/// </summary>
class GravityManager
{
public:
	GravityManager() {};
	~GravityManager() {};

	/// <summary>
	/// ���X�g�폜
	/// </summary>
	void ClearList() { objectDatas_.clear(); }

	/// <summary>
	/// ���X�g�o�^
	/// </summary>
	/// <param name="data"></param>
	void PushList(IObjectData* data) { objectDatas_.push_back(data); }

	/// <summary>
	/// �d�͏���
	/// </summary>
	void CheckGravity();

private:

	list<IObjectData*>objectDatas_;

	float gravity_ = 0.01f;

};

