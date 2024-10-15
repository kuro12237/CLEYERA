#pragma once
#include"ICollider.h"

/// <summary>
/// ���̓����蔻��
/// </summary>
class BoxCollisionManager
{
public:
	BoxCollisionManager() {};
	~BoxCollisionManager() { End(); }

	/// <summary>
	/// �폜
	/// </summary>
	void End();

	/// <summary>
	/// ���X�g�ɓo�^
	/// </summary>
	/// <param name="c"></param>
	void ListPushback(ICollider* c);

	/// <summary>
	/// �o�^�������̂�T��
	/// </summary>
	void CheckAllCollisoin();

private:
	/// <summary>
	/// �o�^��id���폜
	/// </summary>
	void CollidersAllHitsIdsClear();

	/// <summary>
	/// ���X�g�폜
	/// </summary>
	void ListClear();

	/// <summary>
	/// ���������p�x�Z�o
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	float CalculateAngle(float x, float y);

	/// <summary>
	/// �x���𐳋K��
	/// </summary>
	/// <param name="theta"></param>
	/// <returns></returns>
	float NomalizeDegree(float theta);

	/// <summary>
	/// AABB�̃p�����[�^�Ɍ^�ϊ�
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	AABB SettingAABBParam(ICollider* c);

	/// <summary>
	/// �������Ă��邩�̔���
	/// </summary>
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	/// <summary>
	/// �������Z�o
	/// </summary>
	bool CheckBottomCollsion(float t, Math::Vector::Vector4 bDegree);
	/// <summary>
    /// �������Z�o
    /// </summary>
	bool CheckTopCollision(float t, Math::Vector::Vector4 bDegree);
	/// <summary>
    /// �������Z�o
    /// </summary>
	bool CheckLeftCollision(float t, Math::Vector::Vector4 bDegree);
	
	/// <summary>
    /// �������Z�o
    /// </summary>
	bool CheckRightCollision(float t, Math::Vector::Vector4 bDegree);

	/// <summary>
	/// �����o�����Z�o
	/// </summary>
	float BottomExtrusion(ICollider* a, ICollider* b);

	/// <summary>
	/// �����o�����Z�o
	/// </summary>
	float TopExtrusion(ICollider* a, ICollider* b);

	/// <summary>
	/// �����o�����Z�o
	/// </summary>
	float RightExtrusion(ICollider* a, ICollider* b);

	/// <summary>
	/// �����o�����Z�o
	/// </summary>
	float LeftExtrusion(ICollider* a, ICollider* b);

	/// <summary>
	/// �����o���̒l�̊m�F
	/// </summary>
	void CheckExtrusion(ICollider* a, ICollider* b);

	list<ICollider*>colliders_;
};

