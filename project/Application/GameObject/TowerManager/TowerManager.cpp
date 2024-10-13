#include "TowerManager.h"

void TowerManager::Initialize()
{
	auto& transforms = GameObjectManager::GetInstance()->GetObjInstancingData(name_)->GetTransforms();

	for (int i = 0; i < int(transforms.size()); i++)
	{
		shared_ptr<Tower>tower = make_shared<Tower>();
		tower->Initialize(name_, i);
		towers_.push_back(tower);
	}
}

void TowerManager::Update()
{
	//�J���������ɂ��鎞�ɑO�Ƀ��[�v������
	if (p_CameraPos_)
	{
		size_t index = 0;
		auto& transforms = GameObjectManager::GetInstance()->GetObjInstancingData(name_)->GetTransforms();
		for (auto& data : transforms)
		{
			if (data->GetTransform().translate.z <= p_CameraPos_->z)
			{
				Math::Vector::Vector3 newPos = data->GetTransform().translate;
				newPos.z += towerOffset_;
				towers_[index]->SetPos(newPos);
			}
			index++;
		}
	}

	for (shared_ptr<Tower>tower : towers_)
	{
		tower->Update();
	}
}
