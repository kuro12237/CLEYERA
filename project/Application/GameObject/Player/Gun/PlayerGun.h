#pragma 
#include"GameObject/ObjectInterface/IObjectData.h"

/// <summary>
/// �v���C���[�̏e
/// </summary>
class PlayerGun:public IObjectData
{
public:
	PlayerGun() {};
	~PlayerGun() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

#pragma region Set

	void SetTarget(const Math::Vector::Vector3 &t) { targetPos_ = &t; }

	void SetIsDraw(bool flag) { gameObjectManager_->GetObj3dData(name_)->SetIsDraw(flag); }
#pragma endregion


private:

	const Math::Vector::Vector3 *targetPos_ = {};

};