#pragma once

#include"Utility/CollisionMask/CollisionMask.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"
#include"ColliderData.h"
#include"GameObject/ObjectInterface/INameable.h"




/// <summary>
/// 方向
/// </summary>
enum HItDirection {
	NONE,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

class ObjectComponent;

/// <summary>
/// コライダーインターフェース
/// </summary>
class Collider
{
public:
	Collider() {};
	~Collider() {};

	/// <summary>
	/// 当たった時
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(ObjectComponent* objData) { OnCollisionfunc_(objData); }

	/// <summary>
	/// めり込み数値0に
	/// </summary>
	void ClearExtrusion() { extrusion_ = {}; }

	/// <summary>
	/// 当たった方向のqueueをクリア
	/// </summary>
	void ClearHitDirection() { hitDirection_.clear(); }

	/// <summary>
	/// 当たったもののidのqueueを削除
	/// </summary>
	void ClearAllHitsIds();

	/// <summary>
	/// 当たった方向を保存
	/// </summary>
	/// <param name="h"></param>
	void PushBackHitDirection(HItDirection h) { hitDirection_.push_back(h); }


#pragma region  Get
	vector<HItDirection>GetHItDirection() { return hitDirection_; }
	Engine::Transform::TransformEular GetpTransform() { return *pTransform_; }
	AABB GetAABB() { return aabb_; }
	bool GetIsExtrusionFlag() { return isExtrusion_; }
	uint32_t GetId() { return id_; }
	uint32_t GetCollosionAttribute() { return attribute_; }
	uint32_t GetCollisionMask() { return mask_; }
	queue<uint32_t> GetAllHitIds() { return allHitIds; }
	Math::Vector::Vector2 GetExtrusion() { return Math::Vector::Vector2(extrusion_.x,extrusion_.y); }

#pragma endregion

#pragma region Set
	void SetOnCollisionFunc(std::function<void(ObjectComponent* data)>func) { OnCollisionfunc_ = func; }
	void SetObjectData(const Engine::Transform::TransformEular& t) { pTransform_ = &t; }
	void SetId(uint32_t id) { id_ = id; };
	void SetAttribute(uint32_t attribute) { attribute_ = attribute; }
	void SetMask(uint32_t mask) { mask_ = mask; }
	void SetIsExtrusion(bool f) { isExtrusion_ = f; }
	void SetAABB(AABB aabb) { aabb_ = aabb; }
	void SetExtrusion(Math::Vector::Vector2 v) {
		Math::Vector::Vector3 va = Math::Vector::Add({ extrusion_.x, extrusion_.y, 0.0f }, { v.x,v.y,0.0f });
		extrusion_.x = va.x, extrusion_.y = va.y;
	}
	void PushAllHitsIds(uint32_t id) { allHitIds.push(id); }
#pragma endregion

protected:

	bool isExtrusion_ = false;

	Math::Vector::Vector2 extrusion_ = {};
	vector<HItDirection>hitDirection_;
	AABB aabb_{ { -1.0f,-1.0f,-1.0f }, { 1.0f,1.0f,1.0f } };
	uint32_t id_ = 0b000;
	uint32_t attribute_ = 0b000;
	uint32_t mask_ = 0b000;
private:

	std::function<void(ObjectComponent*data)> OnCollisionfunc_ = nullptr;


	const Engine::Transform::TransformEular* pTransform_;
	queue<uint32_t>allHitIds;
};
