#pragma once
#include"GameObject/GameCollider/ICollider.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/ObjectId/GameObjectId.h"

/// <summary>
/// �}�b�v�̃u���b�N�N���X
/// </summary>
class Block :public IObjectData, public ICollider
{
public:
	Block() {};
	~Block() {};

	/// <summary>
	/// ������ 
	/// </summary>
	/// <param name="�O���[�v��"></param>
	/// <param name="�ԍ�"></param>
	void Initialize(string name,uint32_t index);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ������������
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(ICollider* c)override;

private:

	TransformEular initialTransform_{};

};