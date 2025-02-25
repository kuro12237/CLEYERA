#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"

#include"Input.h"
#include"Utility/ObjectId/GameObjectId.h"

/// <summary>
/// クリアシーンでのキャラクターの更新
/// </summary>
class ClearCharacter :public ObjectComponent
{
public:
	ClearCharacter() {};
	~ClearCharacter() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

private:

	SAnimation::Animation animationData_ = {};

	float animFlame_ = 0.0f;

};
