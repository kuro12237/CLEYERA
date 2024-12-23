#pragma once
#include"GameObject/GameCollider/ICollider.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/ObjectId/GameObjectId.h"

/// <summary>
/// マップのブロッククラス
/// </summary>
class Block :public IObjectData
{
public:
	Block() {};
	~Block() {};

	/// <summary>
	/// 初期化 
	/// </summary>
	/// <param name="グループ名"></param>
	/// <param name="番号"></param>
	void Initialize(string name,uint32_t index);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 当たった処理
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(IObjectData* objData)override;

private:

	Engine::Transform::TransformEular initialTransform_{};

};