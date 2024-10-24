#include"CollisionManager.h"



// 衝突判定
void CollisionManager::CheckAllCollision()
{

	std::list<SphereCollider*>::iterator itrSpherre = CollisionManager::GetInstance()->sphereColliders_.begin();
	std::list<SegmentCollider*>::iterator itrSegment = CollisionManager::GetInstance()->segmentColliders_.begin();
	std::list<AABBCollider*>::iterator itrAABB = CollisionManager::GetInstance()->aabbColliders_.begin();
	std::list<OBBCollider*>::iterator itrOBB = CollisionManager::GetInstance()->obbColliders_.begin();

	/* 各種コライダー同士の衝突検出メソッド */
	// SphereとSphere
	CollisionManager::GetInstance()->DetectSphere2SphereList(itrSpherre);
	// AABBとAABB
	CollisionManager::GetInstance()->DetectAABB2AABBList(itrAABB);
	// AABBとSphere
	CollisionManager::GetInstance()->DetectAABB2SphereList(itrAABB, itrSpherre);
	// AABBとSegment
	CollisionManager::GetInstance()->DetectAABB2SegmentList(itrAABB, itrSegment);
	// OBBとSphere
	CollisionManager::GetInstance()->DetectOBB2SphereList(itrOBB, itrSpherre);
	// OBBとSegmetn
	CollisionManager::GetInstance()->DetectOBB2SegmentList(itrOBB, itrSegment);
	// OBBとOBB
	CollisionManager::GetInstance()->DetectOBB2OBBList(itrOBB);


#ifdef _DEBUG

	if (ImGui::TreeNode("CollisionManager"))
	{
		ImGui::Text("SphereColliderList = %d", CollisionManager::GetInstance()->sphereColliders_.size());
		ImGui::Text("SegmentColliderList = %d", CollisionManager::GetInstance()->segmentColliders_.size());
		ImGui::Text("AABBColliderList = %d", CollisionManager::GetInstance()->aabbColliders_.size());
		ImGui::Text("OBBColliderList = %d", CollisionManager::GetInstance()->obbColliders_.size());
		ImGui::TreePop();
	}

#endif // _DEBUG
}



/// <summary>
/// 衝突検出メソッド : Sphere2Sphere
/// </summary>
void CollisionManager::DetectSphere2SphereList(list<SphereCollider*>::iterator itr1) {

	if (itr1 == CollisionManager::GetInstance()->sphereColliders_.end()) {
		return;
	}

	for (; itr1 != CollisionManager::GetInstance()->sphereColliders_.end(); ++itr1) {

		SphereCollider* colliderA = *itr1;

		list<SphereCollider*>::iterator itr2 = itr1;
		itr2++;
		for (; itr2 != CollisionManager::GetInstance()->sphereColliders_.end(); ++itr2) {
			SphereCollider* colliderB = *itr2;

			CheckCollisionSpherexSphere(colliderA, colliderB);
		}
	}
}

/// <summary>
/// 衝突検出メソッド : AABB2AABB
/// </summary>
void CollisionManager::DetectAABB2AABBList(list<AABBCollider*>::iterator itrA) {

	if (itrA == CollisionManager::GetInstance()->aabbColliders_.end()) {
		return;
	}

	for (; itrA != CollisionManager::GetInstance()->aabbColliders_.end(); ++itrA) {

		AABBCollider* colliderA= *itrA;

		list<AABBCollider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != CollisionManager::GetInstance()->aabbColliders_.end(); ++itrB) {
			AABBCollider* colliderB = *itrB;

			CheckCollisionAABBxAABB(colliderA, colliderB);
		}
	}
}

/// <summary>
/// 衝突検出メソッド : AABB2Sphere
/// </summary>
void CollisionManager::DetectAABB2SphereList(list<AABBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB) {

	if (itrA == CollisionManager::GetInstance()->aabbColliders_.end() || itrB == CollisionManager::GetInstance()->sphereColliders_.end()) {
		return;
	}

	for (; itrA != CollisionManager::GetInstance()->aabbColliders_.end(); ++itrA) {

		AABBCollider* colliderA = *itrA;

		list<SphereCollider*>::iterator newItrB = itrB;
		newItrB++;
		for (; newItrB != CollisionManager::GetInstance()->sphereColliders_.end(); ++newItrB) {
			SphereCollider* colliderB = *newItrB;

			CheckCollisionAABBxSphere(colliderA, colliderB);
		}
	}
}

/// <summary>
/// 衝突検出メソッド : AABB2Segment
/// </summary>
void CollisionManager::DetectAABB2SegmentList(list<AABBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB) {

	if (itrA == CollisionManager::GetInstance()->aabbColliders_.end() || itrB == CollisionManager::GetInstance()->segmentColliders_.end()) {
		return;
	}

	for (; itrA != CollisionManager::GetInstance()->aabbColliders_.end(); ++itrA) {

		AABBCollider* colliderA = *itrA;

		list<SegmentCollider*>::iterator newItrB = itrB;
		newItrB++;
		for (; newItrB != CollisionManager::GetInstance()->segmentColliders_.end(); ++newItrB) {
			SegmentCollider* colliderB = *newItrB;

			CheckCollisionAABBxSegment(colliderA, colliderB);
		}
	}
}

/// <summary>
/// 衝突検出メソッド : OBB2Sphere
/// </summary>
void CollisionManager::DetectOBB2SphereList(list<OBBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB) {

	if (itrA == CollisionManager::GetInstance()->obbColliders_.end() || itrB == CollisionManager::GetInstance()->sphereColliders_.end()) {
		return;
	}

	for (; itrA != CollisionManager::GetInstance()->obbColliders_.end(); ++itrA) {

		OBBCollider* colliderA = *itrA;

		// newItrBをsphereColliders_リストの先頭に初期化
		list<SphereCollider*>::iterator newItrB = CollisionManager::GetInstance()->sphereColliders_.begin();
		for (; newItrB != CollisionManager::GetInstance()->sphereColliders_.end(); ++newItrB) {
			SphereCollider* colliderB = *newItrB;

			CheckCollisionOBBxSphere(colliderA, colliderB);
		}
	}
}

/// <summary>
/// 衝突検出メソッド : OBB2Segment
/// </summary>
void CollisionManager::DetectOBB2SegmentList(list<OBBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB) {

	if (itrA == CollisionManager::GetInstance()->obbColliders_.end() || itrB == CollisionManager::GetInstance()->segmentColliders_.end()) {
		return;
	}

	for (; itrA != CollisionManager::GetInstance()->obbColliders_.end(); ++itrA) {

		OBBCollider* colliderA = *itrA;

		list<SegmentCollider*>::iterator newItrB = itrB;
		newItrB++;
		for (; newItrB != CollisionManager::GetInstance()->segmentColliders_.end(); ++newItrB) {
			SegmentCollider* colliderB = *newItrB;

			CheckCollisionOBBxSegment(colliderA, colliderB);
		}
	}
}

/// <summary>
/// 衝突検出メソッド : OBB2OBB
/// </summary>
void CollisionManager::DetectOBB2OBBList(list<OBBCollider*>::iterator itrA) {

	if (itrA == CollisionManager::GetInstance()->obbColliders_.end()) {
		return;
	}

	for (; itrA != CollisionManager::GetInstance()->obbColliders_.end(); ++itrA) {

		OBBCollider* colliderA = *itrA;

		list<OBBCollider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != CollisionManager::GetInstance()->obbColliders_.end(); ++itrB) {
			OBBCollider* colliderB = *itrB;

			CheckCollisionOBBxOBB(colliderA, colliderB);
		}
	}
}



/// <summary>
/// 2つのコライダーの衝突検出と応答メソッド
///  : Sphere2Sphere
/// </summary>
void CollisionManager::CheckCollisionSpherexSphere(SphereCollider* cA, SphereCollider* cB) {

	// コリジョンフィルタリング
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0) 
	{
		return;
	}

	// 値を入れた構造体を作る
	Sphere SphereA = {
		.center = cA->GetSphereColliderWorldPos(),
		.radius = cA->GetRadius(),
	};
	Sphere SphereB = {
		.center = cB->GetSphereColliderWorldPos(),
		.radius = cB->GetRadius(),
	};

	// 衝突判定
	if (Collision::IsCollision(SphereA, SphereB)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

/// <summary>
/// 2つのコライダーの衝突検出と応答メソッド
///  : AABB2AABB
/// </summary>
void CollisionManager::CheckCollisionAABBxAABB(AABBCollider* cA, AABBCollider* cB) {

	// コリジョンフィルタリング
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	// 値を入れた構造体を作る
	AABB aabbA = SettingAABBProperties(cA);
	AABB aabbB = SettingAABBProperties(cB);

	// 衝突判定
	if (Collision::IsCollision(aabbA, aabbB)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

/// <summary>
/// 2つのコライダーの衝突検出と応答メソッド
///  : AABB2Sphere
/// </summary>
void CollisionManager::CheckCollisionAABBxSphere(AABBCollider* cA, SphereCollider* cB) {

	// コリジョンフィルタリング
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	// 値を入れた構造体を作る
	AABB aabb = SettingAABBProperties(cA);
	Sphere sphere = {
		.center = cB->GetSphereColliderWorldPos(),
		.radius = cB->GetRadius(),
	};

	// 衝突判定
	if (Collision::IsCollision(aabb, sphere)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

/// <summary>
/// 2つのコライダーの衝突検出と応答メソッド
///  : AABB2Segment
/// </summary>
void CollisionManager::CheckCollisionAABBxSegment(AABBCollider* cA, SegmentCollider* cB) {

	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	/*if (Collision::IsCollision(cA->GetAABB(), cB->GetSegments())) {
		

	}*/
}

/// <summary>
/// 2つのコライダーの衝突検出と応答メソッド
///  : OBB2Sphere
/// </summary>
void CollisionManager::CheckCollisionOBBxSphere(OBBCollider* cA, SphereCollider* cB) {

	// コリジョンフィルタリング
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	// 値を入れた構造体を作る
	OBB obb = SettingOBBProperties(cA);
	Sphere sphere = {
		.center = cB->GetSphereColliderWorldPos(),
		.radius = cB->GetRadius(),
	};

	// 衝突判定
	if (Collision::IsCollision(obb, sphere)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

/// <summary>
/// 2つのコライダーの衝突検出と応答メソッド
///  : OBB2Segment
/// </summary>
void CollisionManager::CheckCollisionOBBxSegment(OBBCollider* cA, SegmentCollider* cB) {

	// コリジョンフィルタリング
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	//// 値を入れた構造体を作る
	//OBB obb = SettingOBBProperties(cA);
	//Segment segment = {};

	//// 衝突判定
	//if (Collision::IsCollision(obb, segment)) {
	//	cA->OnCollision(cB->GetID());
	//	cB->OnCollision(cA->GetID());
	//}
}

/// <summary>
/// 2つのコライダーの衝突検出と応答メソッド
///  : OBB2OBB
/// </summary>
void CollisionManager::CheckCollisionOBBxOBB(OBBCollider* cA, OBBCollider* cB) {

	// コリジョンフィルタリング
	if (cA->GetID() != enemyID) {

		if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
			(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
		{
			return;
		}
	}

	// 値を入れた構造体を作る
	OBB obbA = SettingOBBProperties(cA);
	OBB obbB = SettingOBBProperties(cB);

	// 衝突判定
	if (Collision::IsCollision(obbA, obbB)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}