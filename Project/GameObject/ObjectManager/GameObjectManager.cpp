#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::GetInstance()
{
	static GameObjectManager instance;
	return &instance;
}

void GameObjectManager::CopyData(LevelData* data)
{
	obj3dData_ = move(data->obj3dData);
	objInstancing3dData_ = move(data->objInstancing3dData);
}

void GameObjectManager::SetAllParents()
{
	for (auto& data : obj3dData_) {
		auto& it = data.second;
		if (!it.childName_.empty())
		{
			for (string name : it.childName_)
			{
				SetParent(it.objectName, name);
				checkChildren(obj3dData_[name]);
			}
		}
	}
}

void GameObjectManager::ObjDataUpdate(IObjectData *data)
{
	if (data)
	{
		TransformEular transform = data->GetTransform();
		string name = data->GetName();
		obj3dData_[name].worldTransform.scale = transform.scale;
		obj3dData_[name].worldTransform.rotation = transform.rotate;
		obj3dData_[name].worldTransform.translate = transform.translate;

		obj3dData_[name].worldTransform.UpdateMatrix();
		obj3dData_[name].worldTransform.TransfarMatrix();
		dataName_.push_back(name);
	}
}

void GameObjectManager::InstancingObjDataUpdate(vector<shared_ptr<IGameInstancing3dObject>>data,string name)
{
	uint32_t size = uint32_t(data.size());

	for (uint32_t i = 0; i < size; i++)
	{
		data[i]->Update();
		objInstancing3dData_[name].GameInstancingObject->PushVector(data[i],i);
	}

	objInstancing3dData_[name].GameInstancingObject->Transfar();
	instancingDataName_.push_back(name);
}

void GameObjectManager::Update()
{
	//すでにアップデートしていたら更新しない
	for (auto& data : obj3dData_) {
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
		//更新しない
		if (!updateFlag)
		{
			continue;
		}
		it.worldTransform.UpdateMatrix();
	}

	dataName_.clear();

	for (auto& data : objInstancing3dData_) {
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

void GameObjectManager::ImGuiUpdate()
{
	if (ImGui::TreeNode("GameObjectManager"))
	{
		ImGui::Text("Game3dObjectSize:%d", obj3dData_.size());

		ImGui::TreePop();
	}
}

void GameObjectManager::Draw()
{
	//normal
	for (auto& data : obj3dData_) {
		auto& it = data.second;
		if (it.gameObject)
		{
			it.gameObject->Draw(it.worldTransform);
		}
	}
	//instancing
	for (auto& data : objInstancing3dData_)
	{
		auto& it = data.second;
		it.GameInstancingObject->Draw();
	}

}

void GameObjectManager::ClearAllData()
{
	obj3dData_.clear();
	cameraData_.clear();
	objInstancing3dData_.clear();
	dataName_.clear();
	instancingDataName_.clear();
}

Game3dObjectData& GameObjectManager::GetObj3dData(string name)
{
	return obj3dData_[name];
}

Game3dInstancingObjectData& GameObjectManager::GetObjInstancingData(string name)
{
	return objInstancing3dData_[name];
}

void GameObjectManager::SetParent(string parentName, string childName)
{
	obj3dData_[childName].worldTransform.parent = &obj3dData_[parentName].worldTransform;
}

void GameObjectManager::checkChildren(Game3dObjectData &data)
{
	if (!data.childName_.empty())
	{
		for (string name : data.childName_)
		{
			SetParent(data.objectName, name);
		}
	}
}
