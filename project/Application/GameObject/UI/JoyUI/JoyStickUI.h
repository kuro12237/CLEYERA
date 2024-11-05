#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"

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
	void Initilaize(const string& joy);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void ImGuiUpdate()override;

private:

	float stickRad_ = 0.0f;
	float lerpFactor_ = 0.0f;

	Math::Vector::Vector3 interTarget_ = {};

};

