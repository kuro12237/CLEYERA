#pragma once
#include"WorldTransform.h"
#include"CameraData.h"

class Sprite;
class ISpriteState
{
public:
	
	virtual ~ISpriteState() {};
	virtual void Initialize(Sprite* state) = 0;
	virtual void Draw(Sprite* state, WorldTransform worldTransform, CameraData view) = 0;

};


