#pragma once
#include"Pch.h"

class GameManager;
/// <summary>
/// シーンインターフェース
/// </summary>
class IScene
{
public:
	IScene() {};
	virtual ~IScene() {};
	virtual void Initialize() = 0;
	virtual void Update([[maybe_unused]] GameManager* state) = 0;
	void PostProcessFuncDraw();
	void Back2dSpriteFuncDraw() ;
	void Object3dFuncDraw() ;
	void Flont2dSpriteFuncDraw() ;

#pragma region Get

	std::function<void()> GetIsPostEffectDrawFunc() { return postEffectDrawFunc_; }

#pragma endregion

	void SetPostEffectDrawFunc(std::function<void()> f) { postEffectDrawFunc_ = f; }
	void SetBack2dSpriteDrawFunc(std::function<void()> f) { back2dSpriteDrawFunc_ = f; }
	void SetObject3dDrawFunc(std::function<void()> f) { object3dDrawFunc_ = f; }
	void SetFlont2dSpriteDrawFunc(std::function<void()> f) { flont2dSpriteDrawFunc_ = f; }

private:
	std::function<void()>postEffectDrawFunc_ = nullptr;
	std::function<void()>back2dSpriteDrawFunc_ = nullptr;
	std::function<void()>object3dDrawFunc_ = nullptr;
	std::function<void()>flont2dSpriteDrawFunc_ = nullptr;
};

