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
	void SetPlayerPos(const Math::Vector::Vector3& pos) { playerPos_ = &pos; }
	void SetPlayerVelo(const Math::Vector::Vector3& velo) { playerVelo_ = &velo; }

	void SetIsDraw(bool flag) { gameObjectManager_->GetObj3dData(name_)->SetIsDraw(flag); }
#pragma endregion


private:

	const Math::Vector::Vector3 *targetPos_ = {};
	const Math::Vector::Vector3* playerVelo_ = nullptr;
	const Math::Vector::Vector3* playerPos_ = nullptr;


};