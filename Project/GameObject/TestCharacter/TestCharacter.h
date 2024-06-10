#pragma once
#include"GameObject/Character/IObjectData.h"

class TestCharacter : public IObjectData
{
public:
	TestCharacter() {};
	~TestCharacter() {};

	void Initialize();

	void Update();

	void Draw();

private:



};
