#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::GetInstance()
{
	static GameObjectManager instance;
	return &instance;
}

void GameObjectManager::CopyData(LevelData* data)
{
	obj3dData_ = data->obj3dData;
	objInstancing3dData_ = data->objInstancing3dData;
	cameraData_ = data->cameraData;
}

void GameObjectManager::SetAllParents()
{
	for (auto& data : obj3dData_) {
		auto& it = data.second;
		if (!it->GetChildsName().empty())
		{
			for (string name : it->GetChildsName())
			{

				if (obj3dData_.find(name) != obj3dData_.end())
				{
					SetParent(it->GetObjectName(), name);
					checkChildren(obj3dData_[name]);
				}
				else
				{
					cameraData_[name]->SetParent(obj3dData_[it->GetObjectName()]->GetWorldTransform());
				}
			}
		}
	}
}

void GameObjectManager::ObjDataUpdate(IObjectData* data)
{
	if (data)
	{
		TransformEular transform = data->GetTransform();
		string name = data->GetName();
		obj3dData_[name]->WtUpdate(transform);
		dataName_.push_back(name);
	}
}

void GameObjectManager::InstancingObjDataUpdate(vector<shared_ptr<IGameInstancing3dObject>>data, string name)
{
	uint32_t size = uint32_t(data.size());

	for (uint32_t i = 0; i < size; i++)
	{
		data[i]->Update();
		objInstancing3dData_[name]->PushObjectData(data[i], i);
	}

	objInstancing3dData_[name]->TransfarData();
	instancingDataName_.push_back(name);
}

void GameObjectManager::CameraUpdate(IObjectData* data)
{
	if (data)
	{
		TransformEular transform = data->GetTransform();
		string name = data->GetName();
		cameraData_[data->GetName()]->WtUpdate(transform);
		cameraData_[data->GetName()]->Update();
		dataName_.push_back(name);
	}
}

void GameObjectManager::Update()
{
	//camera
	for (auto& data : cameraData_)
	{
		auto& it = data.second;
		it->Update();
	}


	// normal
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

	//instancing
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
	cameraData_["PlayerCamera"]->Update();
}

void GameObjectManager::ImGuiUpdate()
{
	if (ImGui::TreeNode("GameObjectManager"))
	{
		ImGui::Text("Game3dObjectSize:: %d", obj3dData_.size());
		//normal3dData
		if (ImGui::TreeNode("obj3dData"))
		{
			for (auto& data : obj3dData_)
			{
				auto& it = data.second;
				it->ImGuiUpdate(it->GetObjectName());
			}
			ImGui::TreePop();
		}
		ImGui::Separator();
		//cameraData
		if (ImGui::TreeNode("cameraData"))
		{
			for (auto& data : cameraData_)
			{
				auto& it = data.second;
				it->ImGuiUpdate(it->GetObjectName());

			}
			ImGui::TreePop();
		}
		ImGui::Separator();
		//カメラ設定
		if (ImGui::TreeNode("CmareSelect")) 
		{
			static char buffer[256] = "";
			if (ImGui::InputText("Text Input", buffer, sizeof(buffer)))
			{
				inputTextSelectCamera_ = std::string(buffer);
			}
			string bottonTitle = "Select_" + inputTextSelectCamera_;
			if (ImGui::Button(bottonTitle.c_str()))
			{
				CameraReset(inputTextSelectCamera_);
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
}

void GameObjectManager::Draw()
{
	//normal
	for (auto& data : obj3dData_) {
		auto& it = data.second;

		auto& obj = it->GetGameObject();
		if (obj && it->GetIsDraw())
		{
			auto& wt = it->GetWorldTransform();
			obj->Draw(wt);
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
	//obj3dData_.clear();
	cameraData_.clear();

	for (auto& data : objInstancing3dData_)
	{
		auto& it = data.second->GetTransforms();
		it.clear();
	}

	dataName_.clear();
	instancingDataName_.clear();
}

shared_ptr<Game3dObjectData>& GameObjectManager::GetObj3dData(string name)
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

void GameObjectManager::CameraReset(string name)
{
	if (name == "")
	{
		auto data = cameraData_.begin();
		auto it = data->second;
		it->Update();
		CameraManager::GetInstance()->ResetCamera(it->GetCamera());
		return;
	}
	if (cameraData_.find(name) != cameraData_.end())
	{
		cameraData_[name]->Update();
		CameraManager::GetInstance()->ResetCamera(cameraData_[name]->GetCamera());
	}
	else
	{
		//入力したの名前のカメラオブジェクトは存在しない
		assert(0);
	}
}

void GameObjectManager::checkChildren(shared_ptr<Game3dObjectData>& data)
{
	if (!data->GetChildsName().empty())
	{
		for (string name : data->GetChildsName())
		{
			if (obj3dData_.find(name) != obj3dData_.end())
			{
				cameraData_[name]->SetParent(obj3dData_[data->GetObjectName()]->GetWorldTransform());
				continue;
			}
			SetParent(data->GetObjectName(), name);
		}
	}
}
