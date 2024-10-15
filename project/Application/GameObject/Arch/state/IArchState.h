#pragma once
#include"../Arch.h"

/// <summary>
/// ステートインターフェース
/// </summary>
class IArchState
{
public:
	IArchState() {};
	~IArchState() {};

	virtual void Initialize()=0;

	virtual void Update() = 0;

private:

};
