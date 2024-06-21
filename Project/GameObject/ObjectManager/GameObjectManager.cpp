#include "GameObjectManager.h"

void GameObjectManager::CopyData(LevelData* data)
{
	obj3dData = move(data->obj3dData);
	objInstancing3dData = move(data->objInstancing3dData);
}

void GameObjectManager::ObjDataUpdate(IObjectData *data)
{
	TransformEular transform= data->GetTransform();
	string name = data->GetName();
	obj3dData[name].worldTransform.scale = transform.scale;
	obj3dData[name].worldTransform.rotation = transform.rotate;
	obj3dData[name].worldTransform.translate = transform.translate;

	obj3dData[name].worldTransform.UpdateMatrix();
	obj3dData[name].worldTransform.TransfarMatrix();
	dataName_.push_back(name);
}

void GameObjectManager::InstancingObjDataUpdate(string name)
{
	objInstancing3dData[name].GameInstancingObject->Transfar();
	dataName_.push_back(name);
}

void GameObjectManager::Update()
{
	for (auto& data : obj3dData) {
		auto& it = data.second;
		int index = 0;
		bool updateFlag = true;
		for (string& name : dataName_) 
		{
			if (it.objectName == name)
			{
				dataName_[index].erase();
				updateFlag = false;
			}
			index++;
		}
		//XV‚µ‚È‚¢
		if (!updateFlag)
		{
			continue;
		}
		it.worldTransform.UpdateMatrix();
	}

	dataName_.clear();

	for (auto& data : objInstancing3dData) {
		auto& it = data.second;
		//int index = 0;
		it.GameInstancingObject->Transfar();
	}
}

void GameObjectManager::Draw()
{
	//normal
	for (auto& data : obj3dData) {
		auto& it = data.second;
		it.gameObject->Draw(it.worldTransform);
	}
	//instancing
	for (auto& data : objInstancing3dData)
	{
		auto& it = data.second;
		it.GameInstancingObject->Draw();
	}

}

Game3dObjectData& GameObjectManager::GetObj3dData(string name)
{
	return obj3dData[name];
}
