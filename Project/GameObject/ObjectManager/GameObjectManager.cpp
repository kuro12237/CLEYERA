#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::GetInstance()
{
	static GameObjectManager instance;
	return &instance;
}

void GameObjectManager::CopyData(LevelData* data)
{
	obj3dData_ = move(data->obj3dData);
	objInstancing3dData_ = data->objInstancing3dData;

}

void GameObjectManager::SetAllParents()
{
	for (auto& data : obj3dData_) {
		auto& it = data.second;
		if (!it->GetChildsName().empty())
		{
			for (string name : it->GetChildsName())
			{
				SetParent(it->GetObjectName(), name);
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
		obj3dData_[name]->WtUpdate(transform);
		dataName_.push_back(name);
	}
}

void GameObjectManager::InstancingObjDataUpdate(vector<shared_ptr<IGameInstancing3dObject>>data,string name)
{
	uint32_t size = uint32_t(data.size());

	for (uint32_t i = 0; i < size; i++)
	{
		data[i]->Update();
		objInstancing3dData_[name]->PushObjectData(data[i],i);
	}

	objInstancing3dData_[name]->TransfarData();
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
			if (it->GetObjectName() == name)
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
		auto& itWt = data.second->GetWorldTransform();
		itWt.UpdateMatrix();
	}

	dataName_.clear();

	for (auto& data : objInstancing3dData_) {
		auto& it = data.second;
		int index = 0;
		bool updateFlag = true;

		for (string& name : instancingDataName_)
		{
			if (it->GetObjectType() == name)
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
		auto& itObj = data.second->GetGameObject();
		auto& itWt = data.second->GetWorldTransform();
		if (itObj)
		{
			itObj->Draw(itWt);
		}
	}
	//instancing
	for (auto& data : objInstancing3dData_)
	{
		auto& it = data.second->GetGameObject();
		it->Draw();
	}

}

void GameObjectManager::ClearAllData()
{
	obj3dData_.clear();
	cameraData_.clear();

	for (auto& data : objInstancing3dData_)
	{
		auto& it = data.second->GetTransforms();
		it.clear();
	}

	dataName_.clear();
	instancingDataName_.clear();
}

unique_ptr<Game3dObjectData>& GameObjectManager::GetObj3dData(string name)
{
	return obj3dData_[name];
}

shared_ptr<Game3dInstancingObjectData>& GameObjectManager::GetObjInstancingData(string name)
{
	return objInstancing3dData_[name];
}

void GameObjectManager::SetParent(string parentName, string childName)
{
	obj3dData_[childName]->SetParent(obj3dData_[parentName]->GetWorldTransform());
}

void GameObjectManager::checkChildren(unique_ptr<Game3dObjectData> &data)
{
	if (!data->GetChildsName().empty())
	{
		for (string name : data->GetChildsName())
		{
			SetParent(data->GetObjectName(), name);
		}
	}
}
