#pragma once
#include"GameObject/ObjectInterface/IObjectData.h"

class GameOverText:public IObjectData
{
public:
	GameOverText() {};
	~GameOverText() {};

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize();

	/// <summary>
	/// XV
	/// </summary>
	void Update();


private:

	float flame_ = 0.0f;
	float flameMax_ = 1.0f;

	float scaleMax_ = 4.0f;

};