#pragma once
#include"Utility/LevelData/LevelData.h"


class GameObjectManager
{
public:

	static GameObjectManager* GetInstance();

	/// <summary>
	/// levelData�̒��g���ړ�
	/// </summary>
	/// <param name="data"></param>
	void MoveData(LevelData* data);

	/// <summary>
	/// ��������ׂĂ̂��̂ɐe�q�֌W������`�F�b�N��������e�q�֌W������
	/// </summary>
	void SetAllParents();

#pragma region Update

	void Update();

	void ImGuiUpdate();

#pragma endregion

	/// <summary>
	/// �\��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I�u�W�F�N�g��o�^
	/// </summary>
	/// <param name="data"></param>
	/// <param name="name"></param>
	void PushObj3dData(shared_ptr<Game3dObjectData>& data, string name) { obj3dData_[name] = move(data); };

	/// <summary>
	/// �I�u�W�F�N�g�폜
	/// </summary>
	/// <param name="name"></param>
	void ClearObj3dData(string name) { obj3dData_.erase(name); }

	/// <summary>
	/// ���ׂĂ��폜
	/// </summary>
	void ClearAllData();

#pragma region Get

	shared_ptr<Game3dObjectData>& GetObj3dData(string name) { return obj3dData_[name]; };
	const shared_ptr<Game3dObjectData>& GetObj3dData_ptr(string name) { return obj3dData_[name]; }
	std::map<string, shared_ptr<Game3dObjectData>>& GetObj3dDatas() { return obj3dData_; }

	shared_ptr<GameCameraData>& GetCameraData(string name) { return cameraData_[name]; }
	shared_ptr<Game3dInstancingObjectData>& GetObjInstancingData(string name) { return objInstancing3dData_[name]; };

	Game3dObjectDesc& GetObjectDesc(string name) { return obj3dData_[name]->GetDesc(); }

#pragma endregion

#pragma region Set
	void SetNormalObjectParent(string parentName, string childName);
	void SetInstancingObjectParent(string parentName, string childName);
	void CameraReset(string name = "");
	void SetObjectPipline(unique_ptr<IPipelineCommand> piplineSelect, string name);
#pragma endregion

private:

	void checkChildren(shared_ptr<Game3dObjectData>& data);

	string inputTextSelectCamera_ = "";

	std::map<string, shared_ptr<Game3dObjectData>> obj3dData_;
	std::map<string, shared_ptr<Game3dInstancingObjectData>>objInstancing3dData_;
	std::map<string, shared_ptr<GameCameraData>>cameraData_;

	std::map<string, shared_ptr<Particle::GpuParticle>>particles_;
	std::map<string, shared_ptr<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>>particleEmitters_;

#pragma region singleton
	GameObjectManager() = default;
	~GameObjectManager() = default;
	GameObjectManager(const  GameObjectManager&) = delete;
	const  GameObjectManager& operator=(const GameObjectManager&) = delete;
#pragma endregion

};

