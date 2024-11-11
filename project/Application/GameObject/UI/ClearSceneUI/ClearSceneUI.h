#pragma once
#include"Sprite/Sprite.h"
#include"../ISceneUI.h"

#include"../BaseSceneBottonUI/BaseBottonUI.h"


/// <summary>
/// ƒQ[ƒ€’†‚ÌUI
/// </summary>
class ClearSceneUI :public ISceneUI
{
public:
	ClearSceneUI() {};
	~ClearSceneUI() {};

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// XV
	/// </summary>
	void Update()override;

private:

};
