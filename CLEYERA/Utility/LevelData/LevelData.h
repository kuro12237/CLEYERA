#pragma once
#include"Game3dObject.h"
#include"WorldTransform.h"

#include"Game3dInstancingObject/GameInstancing3dObject.h"
#include"Transform/STransformEular.h"

struct  Game3dObjectData
{
	std::string objectName;
	std::string modelFileNmae;
	WorldTransform worldTransform;
	Game3dObjectDesc objectDesc;
	unique_ptr<Game3dObject>gameObject;
	uint32_t modelHandle = 0;
	vector<string>childName_;
};

struct  Game3dInstancingObjectData
{
	string objectType;
	std::string modelFileName;
	unique_ptr<GameInstancing3dObject>GameInstancingObject = nullptr;
	vector<shared_ptr<IGameInstancing3dObject>>transform_;
	uint32_t modelHandle = 0;
};

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
	std::map<string,Game3dObjectData> obj3dData;
	std::map<string,Game3dInstancingObjectData>objInstancing3dData;
};
