#pragma once
#include"GameObject/GameCollider/ICollider.h"
#include"Utility/ObjectId/GameObjectId.h"

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"

/// <summary>
/// ���̃N���X
/// </summary>
class Tower :public IObjectData
{
public:
	Tower() {};
	~Tower() {};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="name"></param>
	/// <param name="index"></param>
	void Initialize(string name, uint32_t index);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

#pragma region Set
	void SetPos(const Math::Vector::Vector3& newPos);
#pragma endregion

private:

	uint32_t index_ = 0;
	GameObjectManager* gameObjectManager_ = nullptr;
	Engine::Transform::TransformEular initialTransform_ = {};
	Math::Vector::Vector3 newPos_ = {};
	bool isSetNewPos_ = false;
};