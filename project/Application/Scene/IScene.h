#pragma once
#include"Pch.h"
#include"Cleyera.h"
#include"Utility/ObjectManager/GameObjectManager.h"

#include"GameObject/ObjectInterface/ManagerComponent.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"GameObject/ObjectInterface/IParticleData.h"

class GameManager;
/// <summary>
/// シーンインターフェース
/// </summary>
class IScene
{
public:
	IScene() { postEffect_ = Engine::PostEffect::GetInstance(), gameObjectManager_ = GameObjectManager::GetInstance(); globalVariables_ = GlobalVariables::GetInstance(); };
	virtual ~IScene() {};

	virtual void Initialize(GameManager* state) = 0;
	virtual void Update(GameManager* state) = 0;
	void PostProcessFuncDraw();
	void Back2dSpriteFuncDraw();
	void Object3dFuncDraw();
	void Flont2dSpriteFuncDraw();

#pragma region Get

	std::function<void()> GetIsPostEffectDrawFunc() { return postEffectDrawFunc_; }

#pragma endregion

	void SetPostEffectDrawFunc(std::function<void()> f) { postEffectDrawFunc_ = f; }
	void SetBack2dSpriteDrawFunc(std::function<void()> f) { back2dSpriteDrawFunc_ = f; }
	void SetObject3dDrawFunc(std::function<void()> f) { object3dDrawFunc_ = f; }
	void SetFlont2dSpriteDrawFunc(std::function<void()> f) { flont2dSpriteDrawFunc_ = f; }

protected:


	Engine::PostEffect* postEffect_ = nullptr;
	GameObjectManager* gameObjectManager_ = nullptr;
	GlobalVariables* globalVariables_ = nullptr;


	list<ManagerComponent*>managerList_;
	list<IParticleData*>particleList_;
	list<IObjectData*>objctDataList_;

private:
	std::function<void()>postEffectDrawFunc_ = nullptr;
	std::function<void()>back2dSpriteDrawFunc_ = nullptr;
	std::function<void()>object3dDrawFunc_ = nullptr;
	std::function<void()>flont2dSpriteDrawFunc_ = nullptr;
};

