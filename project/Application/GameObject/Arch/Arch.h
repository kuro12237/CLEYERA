#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"state/IArchState.h"

/// <summary>
/// �^�C�g���̔�
/// </summary>
class Arch :public IObjectData
{
public:
	Arch() {};
	~Arch() {};

	/// <summary>
	///  ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

#pragma region Set
	void SetStart(bool flag) { isStart_ = flag; }
	void SetCameraPos(const Math::Vector::Vector3& pos) { p_CameraPos_ = &pos; }
#pragma endregion

private:

	bool isStart_ = false;
	const Math::Vector::Vector3* p_CameraPos_ = nullptr;
};
