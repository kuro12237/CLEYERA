#pragma once
#include"JsonComponent.h"
#include"Light/LightingManager.h"

/// <summary>
/// ライト抽象クラス
/// </summary>
class LightComponent:public JsonComponent
{
public:
	LightComponent() { lightManager_ = Engine::Manager::LightingManager::GetInstance(); }
	virtual ~LightComponent() {};

	virtual void Initialize() = 0;

	virtual void Update();

protected:

	/// <summary>
	/// JsonDataの作成
	/// </summary>
	void CreateLightData();

private:

	Engine::Manager::LightingManager* lightManager_ = nullptr;
	Engine::Manager::PointLight_param pointLight_ = {};
};
