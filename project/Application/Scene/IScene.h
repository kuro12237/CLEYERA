#pragma once

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
	virtual void PostProcessDraw() = 0;
	virtual void Back2dSpriteDraw() = 0;
	virtual void Object3dDraw() = 0;
	virtual void Flont2dSpriteDraw() = 0;

private:

};

