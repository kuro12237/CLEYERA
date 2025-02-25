#pragma once
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"Utility/ObjectId/GameObjectId.h"

#include"BreakBlockHp.h"

/// <summary>
/// 壊れるマップのブロッククラス
/// </summary>
class BreakBlock :public ObjectComponent, public Collider
{
public:
	BreakBlock() {};
	~BreakBlock() {};

	/// <summary>
	/// 初期化 
	/// </summary>
	/// <param name="グループ名"></param>
	/// <param name="番号"></param>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 当たった処理
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(ObjectComponent* objData)override;


#pragma region Get

	int32_t GetInstancingIndex() { return instancingIndex_; }
	bool GetIsDead() { return isDead_; }
#pragma endregion

#pragma region Set
	void SetInstanceINdex(uint32_t index) { instancingIndex_ = index; }
	void SetName(string name) { name_ = name; }
#pragma endregion


private:

	Engine::Transform::TransformEular initialTransform_{};

	unique_ptr<BreakBlockHp>hp_ = nullptr;

	int32_t instancingIndex_ = 0;
	bool isDead_ = false;

	vector<uint32_t>texHandles_;
};