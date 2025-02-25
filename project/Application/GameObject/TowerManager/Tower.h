#pragma once
#include"Utility/ObjectId/GameObjectId.h"

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"

/// <summary>
/// 塔のクラス
/// </summary>
class Tower :public ObjectComponent
{
public:
	Tower() {};
	~Tower() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="name"></param>
	/// <param name="index"></param>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

#pragma region Set
	void SetPos(const Math::Vector::Vector3& newPos);
	void SetName(string name) { name_ = name; }
	void SetTowerIndex(uint32_t index) { index_ = index; }
#pragma endregion

private:

	uint32_t index_ = 0;
	GameObjectManager* gameObjectManager_ = nullptr;
	Engine::Transform::TransformEular initialTransform_ = {};
	Math::Vector::Vector3 newPos_ = {};
	bool isSetNewPos_ = false;
};