#include "IScene.h"

void IScene::PostProcessFuncDraw()
{
	if (this->postEffectDrawFunc_)
	{
		postEffectDrawFunc_();
	}
}

void IScene::Back2dSpriteFuncDraw()
{
	if (this->back2dSpriteDrawFunc_)
	{
		back2dSpriteDrawFunc_();
	}
}

void IScene::Object3dFuncDraw()
{
	if (this->object3dDrawFunc_)
	{
		object3dDrawFunc_();
	}
}

void IScene::Flont2dSpriteFuncDraw()
{
	if (flont2dSpriteDrawFunc_)
	{
		flont2dSpriteDrawFunc_();
	}
}
