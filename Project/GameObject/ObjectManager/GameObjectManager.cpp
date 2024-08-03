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
	cameraData_ = move(data->cameraData);
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
		auto& it = data.second->GetWorldTransform();
		it.UpdateMatrix();
		auto& object = data.second->GetGameObject();
		if (object->GetSkinningFlag())
		{
			object->SkinningUpdate();
		}
	}

	//instancing
	for (auto& data : objInstancing3dData_) {
		auto& it = data.second;

		for (uint32_t i = 0; i < it->GetTransforms().size(); i++)
		{
			it->GetTransforms()[i]->Update();
			it->PushObjectData(i);
		}
		it->GetGameObject()->Transfar();
	}
}

void GameObjectManager::ImGuiUpdate()
{
	if (ImGui::TreeNode("GameObjectManager"))
	{
		ImGui::Text("Game3dObjectSize:: %d", obj3dData_.size());
		//normal3dData
		if (ImGui::TreeNode("obj3dData"))
		{
			//ImGui::BeginChild("obj3dData", ImVec2(250, 100));
			for (auto& data : obj3dData_)
			{
				auto& it = data.second;
				it->ImGuiUpdate(it->GetObjectName());
			}
			//ImGui::EndChild();
			ImGui::TreePop();
		}
		ImGui::Separator();
		//instancingData
		if (ImGui::TreeNode("InstancingData"))
		{
			for (auto& data : objInstancing3dData_)
			{
				auto& it = data.second;

				ImGui::BeginChild("objInstancingData", ImVec2(250, 100));
				if (ImGui::TreeNode(it->GetObjectType().c_str()))
				{
					it->ImGuiUpdate();
					ImGui::TreePop();
				}

				ImGui::EndChild();
			}
			ImGui::TreePop();
		}

		//cameraData
		if (ImGui::TreeNode("cameraData"))
		{
			//ImGui::BeginChild("cameraData", ImVec2(250, 100));
			for (auto& data : cameraData_)
			{
				auto& it = data.second;
				it->ImGuiUpdate(it->GetObjectName());

			}
			//ImGui::EndChild();
			ImGui::TreePop();
		}
		ImGui::Separator();
		//カメラ設定
		static char buffer[256] = "";
		if (ImGui::InputText("SelectCameraName", buffer, sizeof(buffer)))
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
		it;
		//it->Draw();
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
