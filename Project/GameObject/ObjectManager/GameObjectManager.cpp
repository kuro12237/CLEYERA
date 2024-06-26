#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::GetInstance()
{
	static GameObjectManager instance;
	return &instance;
}

void GameObjectManager::CopyData(LevelData* data)
{
	obj3dData = move(data->obj3dData);
	objInstancing3dData = move(data->objInstancing3dData);
}

void GameObjectManager::SetAllParents()
{
	for (auto& data : obj3dData) {
		auto& it = data.second;
		if (!it.childName_.empty())
		{
			for (string name : it.childName_)
			{
				SetParent(it.objectName, name);
				checkChildren("", obj3dData[name]);
			}
		}
	}
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

void GameObjectManager::InstancingObjDataUpdate(vector<shared_ptr<IGameInstancing3dObject>>data,string name)
{
	uint32_t size = uint32_t(data.size());

	for (uint32_t i = 0; i < size; i++)
	{
		data[i]->Update();
		objInstancing3dData[name].GameInstancingObject->PushVector(data[i],i);
	}

	objInstancing3dData[name].GameInstancingObject->Transfar();
	instancingDataName_.push_back(name);
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
		int index = 0;
		bool updateFlag = true;

		for (string& name : instancingDataName_)
		{
			if (it.objectType == name)
			{
				updateFlag = false;
			}
			index++;
		}
		if (!updateFlag)
		{
			continue;
		}
		//it.GameInstancingObject->Transfar();
	}
	instancingDataName_.clear();
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

Game3dInstancingObjectData& GameObjectManager::GetObjInstancingData(string name)
{
	return objInstancing3dData[name];
}

void GameObjectManager::SetParent(string parentName, string childName)
{
	obj3dData[childName].worldTransform.parent = &obj3dData[parentName].worldTransform;
}

void GameObjectManager::checkChildren(string name, Game3dObjectData &data)
{
	name;
	if (!data.childName_.empty())
	{
		for (string name : data.childName_)
		{
			SetParent(data.objectName, name);
		}
	}
}
