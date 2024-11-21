#pragma once
#include"GameObject/ObjectInterface/IObjectData.h"

/// <summary>
/// �N���A�R�C������N���X
/// </summary>
class ClearCoin:public IObjectData
{
public:
	ClearCoin() {};
	~ClearCoin() {};

	void Initialize();

	void Update();

#pragma region Set

	
#pragma endregion

private:

	const Math::Vector::Vector3* cameraPos_ = nullptr;
	SAnimation::Animation animationData_{};

	float flame_ = 0.0f;
};
