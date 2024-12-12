#pragma once
#include"GameObject/GameCollider/ICollider.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/ObjectId/GameObjectId.h"

#include"BreakBlockHp.h"

/// <summary>
/// 壊れるマップのブロッククラス
/// </summary>
class BreakBlock :public IObjectData, public ICollider
{
public:
	BreakBlock() {};
	~BreakBlock() {};

	/// <summary>
	/// 初期化 
	/// </summary>
	/// <param name="グループ名"></param>
	/// <param name="番号"></param>
	void Initialize(string name, uint32_t index);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 当たった処理
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(ICollider* c, IObjectData* objData)override;


#pragma region Get

	int32_t GetInstancingIndex() { return instancingIndex_; }
	bool GetIsDead() { return isDead_; }
#pragma endregion


private:

	Engine::Transform::TransformEular initialTransform_{};

	unique_ptr<BreakBlockHp>hp_ = nullptr;

	int32_t instancingIndex_ = 0;
	bool isDead_ = false;

	vector<uint32_t>texHandles_;
};