#pragma once
#include"Lava.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"Utility/ObjectManager/GameObjectManager.h"

/// <summary>
/// �n��̃I�u�W�F���g����N���X
/// </summary>
class Lava :public IObjectData
{
public:
	Lava() {};
	~Lava() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

#pragma region Set
	void SetCameraParent(const Math::Vector::Vector3 &pos) { p_CameraPos_ = &pos; }
#pragma endregion

private:

	const Math::Vector::Vector3* p_CameraPos_ = nullptr;

};