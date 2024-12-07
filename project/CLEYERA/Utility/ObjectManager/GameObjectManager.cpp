#include "GameObjectManager.h"

using namespace Engine::Manager;

GameObjectManager* GameObjectManager::GetInstance()
{
	static GameObjectManager instance;
	return &instance;
}

void GameObjectManager::MoveData(LevelData* data)
{
	obj3dData_ = move(data->obj3dData);
	objInstancing3dData_ = move(data->objInstancing3dData);
	cameraData_ = move(data->cameraData);
}

void GameObjectManager::SetAllParents()
{
	for (auto& data : obj3dData_) {
		auto& it = data.second;
		if (it->GetChildsName().empty())
		{
			continue;
		}

		//子の名前チェック
		for (string name : it->GetChildsName())
		{
			if (obj3dData_.find(name) != obj3dData_.end())
			{
				SetNormalObjectParent(it->GetObjectName(), name);
				CheckChildren(obj3dData_[name]);
			}
			else if (cameraData_.find(name) != cameraData_.end())
			{
				cameraData_[name]->SetParent(obj3dData_[it->GetObjectName()]->GetWorldTransform());
			}

			for (auto& datas : objInstancing3dData_)
			{
				auto& instancingDatas = datas.second;
				for (auto& instancingData : instancingDatas->GetTransforms())
				{
					if (name == instancingData->GetName())
					{
						instancingData->SetParent(it->GetWorldTransform().matWorld);
					}
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
	for (auto& data : obj3dData_) {
		auto& it = data.second->GetWorldTransform();
		it.UpdateMatrix();
		auto& object = data.second->GetGameObject();
		//skinning
		if (object->GetSkinningFlag())
		{
			object->SkinningUpdate();
		}
	}

	//instancing
	for (auto& data : objInstancing3dData_) {
		auto& it = data.second;

		//object
		for (uint32_t i = 0; i < it->GetTransforms().size(); i++)
		{
			//壊れているときすべて0に
			if (it->GetTransforms()[i]->GetBreakFlag() == true)
			{
				it->GetTransforms()[i]->SetTransformEular({});
			}

			it->GetTransforms()[i]->Update();
			it->PushObjectData(i);
		}
		//転送
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
			for (auto& data : obj3dData_)
			{
				auto& it = data.second;
				it->ImGuiUpdate(it->GetObjectName());
			}
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
			for (auto& data : cameraData_)
			{
				auto& it = data.second;
				it->ImGuiUpdate(it->GetObjectName());

			}
			ImGui::TreePop();
		}

		ImGui::Separator();

		//カメラ選択
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



void GameObjectManager::InstancingDraw()
{
	//instancing
	for (auto& data : objInstancing3dData_)
	{
		auto& it = data.second->GetGameObject();
		it->Draw();
	}
}

void GameObjectManager::NormalDraw()
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

void GameObjectManager::DeleateParent(string name)
{
	obj3dData_[name]->DeleateParent();
}

void GameObjectManager::SetNormalObjectParent(string parentName, string childName)
{
	obj3dData_[childName]->SetParent(obj3dData_[parentName]->GetWorldTransform());
}

void GameObjectManager::SetInstancingObjectParent(string parentName, string childName)
{
	parentName;
	objInstancing3dData_[childName];
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

void GameObjectManager::SetObjectPipline(unique_ptr<IPipelineCommand> piplineSelect, string name)
{
	obj3dData_[name]->ChangePipline(move(piplineSelect));
}

void GameObjectManager::CheckChildren(shared_ptr<Game3dObjectData>& data)
{
	if (!data->GetChildsName().empty())
	{
		for (string name : data->GetChildsName())
		{
			if (obj3dData_.find(name) != obj3dData_.end())
			{
				obj3dData_[name]->SetParent(obj3dData_[data->GetObjectName()]->GetWorldTransform());
				continue;
			}
			SetNormalObjectParent(data->GetObjectName(), name);
		}
	}
}
