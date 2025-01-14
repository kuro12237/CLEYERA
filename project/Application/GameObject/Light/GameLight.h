#pragma once
#include"Cleyera.h"
#include"GameObject/ObjectInterface/LightComponent.h"

/// <summary>
/// ゲームのライト
/// </summary>
class GameLight :public LightComponent
{
public:
	GameLight() {};
	~GameLight() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

private:


};
