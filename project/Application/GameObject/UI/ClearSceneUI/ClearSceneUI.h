#pragma once
#include"Sprite/Sprite.h"
#include"../ISceneUI.h"

#include"../BaseSceneBottonUI/BaseBottonUI.h"


/// <summary>
/// �Q�[������UI
/// </summary>
class ClearSceneUI :public ISceneUI
{
public:
	ClearSceneUI() {};
	~ClearSceneUI() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

private:

};
