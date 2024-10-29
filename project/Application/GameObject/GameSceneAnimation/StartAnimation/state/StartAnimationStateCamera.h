#pragma once
#include"../StartAnimation.h"

class StartAnimationStateCamera : public IStartAnimation
{
public:

	~StartAnimationStateCamera() {};

	void Initialize() override;

	void Update(StartAnimation& startAnimation)override;

private:

};
