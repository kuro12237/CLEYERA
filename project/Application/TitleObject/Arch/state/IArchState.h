#pragma once
#include"../Arch.h"

class IArchState
{
public:
	IArchState() {};
	~IArchState() {};

	virtual void Initialize()=0;

	virtual void Update() = 0;

private:

};
