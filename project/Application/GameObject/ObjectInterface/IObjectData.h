#pragma once
#include"WorldTransform.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/GlobalVariables/GlobalVariables.h"

#include"JsonComponent.h"

#include"INameable.h"
#include"../GameCollider/ICollider.h"

class GameObjectManager;

class ICollider;
/// <summary>
/// オブジェクトの抽象クラス
/// </summary>
class IObjectData : public INameable, public JsonComponent
{
public:
	IObjectData();
	virtual ~IObjectData() {};

	void CalcGravity(float g);

	/// <summary>
	/// objectのデータをコライダーにセット
	/// </summary>
	void SetColliderParamData();

	virtual void OnCollision([[maybe_unused]]IObjectData* objectData) {};

	void SetObjectParamData();

#pragma region Set
	void SetVelocity(Math::Vector::Vector3 v) { velocity_ = v; }
#pragma endregion

#pragma region Get
	Math::Vector::Vector3 GetVelocity() { return velocity_; }
	ICollider* GetCollider() { return collider_.get(); }
	weak_ptr<IGameObjectData> GetObjectData() { return objectData_; }
#pragma endregion

private:

protected:

	Math::Vector::Vector3 velocity_{};

	unique_ptr<ICollider>collider_ = nullptr;

	weak_ptr<IGameObjectData>objectData_;

	GameObjectManager* gameObjectManager_ = nullptr;
};

