#pragma once

/// <summary>
/// StartAnimationのインターフェース
/// </summary>
class StartAnimation;
class IStartAnimation
{
public:
	IStartAnimation() = default;
	virtual ~IStartAnimation() {};

	virtual void Initialize() = 0;

	virtual void Update(StartAnimation& startAnimation) = 0;

private:

};
