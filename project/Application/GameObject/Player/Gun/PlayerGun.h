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

#pragma endregion


private:

	const Math::Vector::Vector3 *targetPos_ = {};

};