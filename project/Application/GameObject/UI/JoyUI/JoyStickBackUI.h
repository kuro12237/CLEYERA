#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"

/// <summary>
/// �W���C�X�e�B�b�N�w�i2d�\���N���X
/// </summary>
class JoyStickBackUI :public ISpriteData
{
public:
	JoyStickBackUI() {};
	~JoyStickBackUI() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initilaize(const string &joy);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	void ImGuiUpdate()override;


private:

};
