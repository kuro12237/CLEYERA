#pragma once
#include"Sprite/Sprite.h"
#include"../ISceneUI.h"

#include"../BaseSceneBottonUI/BaseBottonUI.h"



/// <summary>
/// �^�C�g������UI
/// </summary>
class TitleSceneUI :public ISceneUI
{
public:
	TitleSceneUI() {};
	~TitleSceneUI() {};

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