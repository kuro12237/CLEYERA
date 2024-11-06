#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"
#include"GameObject/UI/GameSceneUIData.h"

/// <summary>
/// ジョイスティック2d表示クラス
/// </summary>
class JoyStickUI :public ISpriteData
{
public:
	JoyStickUI() {};
	~JoyStickUI() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="joy"></param>
	void Initilaize(const string &groupName,const JoyStickLeftRight& direction);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void ImGuiUpdate()override;

private:

	JoyStickLeftRight direction_;

	float stickRad_ = 0.0f;
	float lerpFactor_ = 0.0f;

	Math::Vector::Vector3 interTarget_ = {};

};

