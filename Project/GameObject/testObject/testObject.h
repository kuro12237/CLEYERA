#pragma once
#include"GameObject/Character/IObjectData.h"

class testObject :public IObjectData
{
public:
	testObject() {};
	~testObject() {};

	void Initialize();

	void Update();

	void Draw(const CameraData &camera);

private:

};

