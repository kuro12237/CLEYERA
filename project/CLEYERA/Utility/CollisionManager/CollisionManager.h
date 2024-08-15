#pragma once

#include"Pch.h"
#include "Vector/VectorTransform.h"
#include "Matrix/MatrixTransform.h"
#include "IsCollision/IsCollision.h"
#include "ColliderConfig.h"
#include"./Collider/SphereCollider.h"
#include "./Collider/OBBCollider.h"
#include "./Collider/AABBCollider.h"
#include "./Collider/SegmentCollider.h"


/* CollisionManagerクラス */
class CollisionManager {

public:

    /// <summary>
    /// インスタンスの取得
    /// </summary>
    static CollisionManager* GetInstance() {
        static CollisionManager instance;
        return &instance;
    }

	/// <summary>
	/// 登録されたすべてのコライダーに対して衝突を検出する。
	/// </summary>
	static void CheckAllCollision();

    /// <summary>
    /// 各種コライダーをリストに登録するメソッド
    /// </summary>
    static void ColliderSpherePushBack(SphereCollider* collider) { CollisionManager::GetInstance()->sphereColliders_.push_back(collider); }
    static void ColliderSegmentPushBack(SegmentCollider* collider) { CollisionManager::GetInstance()->segmentColliders_.push_back(collider); }
    static void ColliderAABBPushBack(AABBCollider* collider) { CollisionManager::GetInstance()->aabbColliders_.push_back(collider); }
    static void ColliderOBBPushBack(OBBCollider* collider) { CollisionManager::GetInstance()->obbColliders_.push_back(collider); }

    /// <summary>
    /// 登録されたコライダーリストをクリアするメソッド
    /// </summary>
    static void ClliderClear()	{
        CollisionManager::GetInstance()->sphereColliders_.clear();
        CollisionManager::GetInstance()->segmentColliders_.clear();
        CollisionManager::GetInstance()->aabbColliders_.clear();
        CollisionManager::GetInstance()->obbColliders_.clear();
	}


    // -------------------------------------------------------------------------
    // 衝突検出メソッド
    // -------------------------------------------------------------------------
    // 各種コライダー同士の衝突検出メソッド
    // -------------------------------------------------------------------------
    static void DetectSphere2SphereList(list<SphereCollider*>::iterator itrA);
    static void DetectAABB2AABBList(list<AABBCollider*>::iterator itrA);
    static void DetectAABB2SphereList(list<AABBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB);
    static void DetectAABB2SegmentList(list<AABBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB);
    static void DetectOBB2SphereList(list<OBBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB);
    static void DetectOBB2SegmentList(list<OBBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB);
    static void DetectOBB2OBBList(list<OBBCollider*>::iterator itrA);


    // -------------------------------------------------------------------------
    // 衝突検出と応答メソッド
    // -------------------------------------------------------------------------
    // 2つのコライダーの衝突検出と応答メソッド
    // -------------------------------------------------------------------------
    static void CheckCollisionSpherexSphere(SphereCollider* cA, SphereCollider* cB);
    static void CheckCollisionAABBxAABB(AABBCollider* cA, AABBCollider* cB);
    static void CheckCollisionAABBxSphere(AABBCollider* cA, SphereCollider* cB);
    static void CheckCollisionAABBxSegment(AABBCollider* cA, SegmentCollider* cB);
    static void CheckCollisionOBBxSphere(OBBCollider* cA, SphereCollider* cB);
    static void CheckCollisionOBBxSegment(OBBCollider* cA, SegmentCollider* cB);
    static void CheckCollisionOBBxOBB(OBBCollider* cA, OBBCollider* cB);


private:

	// コライダーリスト
	list<SphereCollider*> sphereColliders_;
	list<SegmentCollider*> segmentColliders_;
    list<AABBCollider*> aabbColliders_;
    list<OBBCollider*> obbColliders_;
};

