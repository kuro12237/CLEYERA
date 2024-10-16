#pragma once
#include"ModelManager.h"
#include"Light/DirectionLIght.h"
#include"Game3dObjectDesc.h"
#include"Graphics/PipelineManager/GraphicsPipelineManager.h"
#include"Animation/AnimationManager.h"

#include"Graphics/CallPipline/PipelineHandler.h"

/// <summary>
/// �Q�[���I�u�W�F�N�g�N���Xmodel���Z�b�g���邱�Ƃ�3d���f����\���ł���
/// </summary>
class Game3dObject
{
public:
	Game3dObject() {};
	~Game3dObject() {};

	/// <summary>
	/// �쐻
	/// </summary>
	/// <param name="piplineSelect"></param>
	void Create(unique_ptr<IPipelineCommand> piplineSelect = nullptr);

	/// <summary>
	/// ���f����ݒ�
	/// </summary>
	/// <param name="index"></param>
	void SetModel(uint32_t index);

	/// <summary>
	/// �p�C�v���C���ؑ�
	/// </summary>
	/// <param name="piplineSelect"></param>
	void ChangePipline(unique_ptr<IPipelineCommand> piplineSelect);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="worldTransform"></param>
	void Draw(Engine::Transform::WorldTransform worldTransform);

	/// <summary>
	/// �X�L�j���O�p�̃o�b�t�@�[���쐻
	/// </summary>
	void CreateSkinningParameter();

	/// <summary>
	/// ���X�V
	/// </summary>
	/// <param name="fileName"></param>
	/// <param name="t"></param>
	void SkeletonUpdate(string fileName, float t);

	/// <summary>
	/// �D���l���X�V
	/// </summary>
	void SkinningUpdate();

	/// <summary>
	/// �I�u�W�F�N�g�̖��O��ݒ�
	/// </summary>
	/// <param name="name"></param>
	void SetObjectName(const string& name) { name_ = name; }

#pragma region Set
	void SetDesc(const Game3dObjectDesc& desc) { game3dObjectDesc_ = desc; }
	void SetName(string name) { name_ = name; }
#pragma endregion

#pragma region Get
	SAnimation::Skeleton& GetSkeleton() { return skeleton_; }
	bool GetSkinningFlag() { return skinningFlag_; }
	Game3dObjectDesc& GetDesc() { return game3dObjectDesc_; }
#pragma endregion

private:

	string name_ = "";

	Engine::Objects::Model* model_ = nullptr;
	SModelData modelData_ = {};
	uint32_t prevModelIndex_ = 0;

	unique_ptr<PipelineHandler>piplineHandler_ = nullptr;

	unique_ptr<Engine::Buffer::BufferResource<Material>>MaterialBuffer_ = nullptr;
	Material material_ = {};

	Material MaterialConverter();
	unique_ptr<Engine::Buffer::BufferResource<SkinCluster>>cSkinCluster_ = nullptr;

#pragma region Skinning
	bool skinningFlag_ = false;
	SAnimation::Skeleton skeleton_;
	std::vector<Math::Matrix::Matrix4x4>inverseBindMatrices;
	unique_ptr<Engine::Buffer::BufferResource<WellForGPU>>palette_ = nullptr;
	vector<WellForGPU>paletteParam_;
	//unique_ptr<BufferResource<>>
#pragma endregion

	Game3dObjectDesc game3dObjectDesc_{};

};