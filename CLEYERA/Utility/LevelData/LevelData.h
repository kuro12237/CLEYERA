#pragma once
#include"Game3dObject.h"
#include"WorldTransform.h"

#include"Game3dInstancingObject/GameInstancing3dObject.h"
#include"Transform/STransformEular.h"

#include"Game3dInstancingObjectData.h"
#include"Game3dObjectData.h"

struct GameCameraData
{
	string type;
	CameraData camera;
	WorldTransform worldTransform;
	bool isParent = false;

};

struct LevelData
{
	uint32_t objectNum = 0;
	std::map<string,shared_ptr<Game3dObjectData>> obj3dData;
	std::map<string,shared_ptr<Game3dInstancingObjectData>>objInstancing3dData;
};
