#pragma once
#include"Collider.h"

/// <summary>
/// 箱の当たり判定
/// </summary>
class BoxCollisionManager
{
public:
	BoxCollisionManager() {};
	~BoxCollisionManager() { End(); }

	/// <summary>
	/// 削除
	/// </summary>
	void End();

	/// <summary>
	/// リストに登録
	/// </summary>
	/// <param name="c"></param>
	void ListPushback(ObjectComponent*data);

	/// <summary>
	/// 登録したものを探査
	/// </summary>
	void CheckAllCollisoin();

private:
	/// <summary>
	/// 登録下idを削除
	/// </summary>
	void CollidersAllHitsIdsClear();

	/// <summary>
	/// リスト削除
	/// </summary>
	void ListClear();

	/// <summary>
	/// 当たった角度算出
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	float CalculateAngle(float x, float y);

	/// <summary>
	/// 度数を正規化
	/// </summary>
	/// <param name="theta"></param>
	/// <returns></returns>
	float NomalizeDegree(float theta);

	/// <summary>
	/// AABBのパラメータに型変換
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	AABB SettingAABBParam(Collider* c);

	/// <summary>
	/// 当たっているかの判定
	/// </summary>
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	/// <summary>
	/// 方向を算出
	/// </summary>
	bool CheckBottomCollsion(float t, Math::Vector::Vector4 bDegree);
	/// <summary>
    /// 方向を算出
    /// </summary>
	bool CheckTopCollision(float t, Math::Vector::Vector4 bDegree);
	/// <summary>
    /// 方向を算出
    /// </summary>
	bool CheckLeftCollision(float t, Math::Vector::Vector4 bDegree);
	
	/// <summary>
    /// 方向を算出
    /// </summary>
	bool CheckRightCollision(float t, Math::Vector::Vector4 bDegree);

	/// <summary>
	/// 押し出しを算出
	/// </summary>
	float BottomExtrusion(Collider* a, Collider* b);

	/// <summary>
	/// 押し出しを算出
	/// </summary>
	float TopExtrusion(Collider* a, Collider* b);

	/// <summary>
	/// 押し出しを算出
	/// </summary>
	float RightExtrusion(Collider* a, Collider* b);

	/// <summary>
	/// 押し出しを算出
	/// </summary>
	float LeftExtrusion(Collider* a, Collider* b);

	/// <summary>
	/// 押し出しの値の確認
	/// </summary>
	void CheckExtrusion(Collider* a, Collider* b);

	vector<ObjectComponent*>datas_;

};

