#pragma once

class GameManager;
class IScene
{
public:
    IScene() {};
	virtual ~IScene() {};
	virtual void Initialize() = 0;
	virtual void Update(GameManager* state) = 0;
	virtual void PostProcessDraw() = 0;
	virtual void Back2dSpriteDraw() = 0;
	virtual void Object3dDraw() = 0;
	virtual void Flont2dSpriteDraw() = 0;

private:

};

