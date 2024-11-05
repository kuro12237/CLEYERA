#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"

/// <summary>
/// �W���C�X�e�B�b�N2d�\���N���X
/// </summary>
class JoyStickUI :public ISpriteData
{
public:
	JoyStickUI() {};
	~JoyStickUI() {};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="joy"></param>
	void Initilaize(const string& joy);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	void ImGuiUpdate()override;

private:

	float stickRad_ = 0.0f;
	float lerpFactor_ = 0.0f;

	Math::Vector::Vector3 interTarget_ = {};

};

