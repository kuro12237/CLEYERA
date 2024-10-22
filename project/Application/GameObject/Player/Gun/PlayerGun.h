#pragma 
#include"GameObject/ObjectInterface/IObjectData.h"

/// <summary>
/// プレイヤーの銃
/// </summary>
class PlayerGun:public IObjectData
{
public:
	PlayerGun() {};
	~PlayerGun() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region Set

	void SetTarget(const Math::Vector::Vector3 &t) { targetPos_ = &t; }

#pragma endregion


private:

	const Math::Vector::Vector3 *targetPos_ = {};

};