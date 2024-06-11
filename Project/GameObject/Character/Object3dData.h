#pragma once
#include"Utility/LevelData/LevelData.h"
class Object3dData
{
public:
	Object3dData() {};
	~Object3dData() {};

	void Initialize(LevelData*levelData);

	void Update();

	void Draw();


private:

	map<string,Game3dObjectData>datas_;

};

