#pragma once
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"BufferResources.h"
#include"CreateResource.h"
#include"WorldTransform.h"
#include"Graphics/PipelineManager/GraphicsPipelineManager.h"
#include"Utility/CameraManager/CameraManager.h"
#include"Utility/RuntimeCounter/RunTimeCounter.h"
#include"Emitter/StructGpuParticleEmitter.h"
#include"Model/ModelManager.h"

/// <summary>
/// パーティクル構造体
/// </summary>
struct ParticleCS
{
	Math::Vector::Vector3 translate;
	Math::Vector::Vector3 scale;
	Math::Vector::Vector3 rotate;
	Math::Matrix::Matrix4x4 matWorld;
	float lifeTime;
	Math::Vector::Vector3 velocity;
	float currentTime;
	Math::Vector::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	Math::Vector::Vector4 colorDecay = { 0.0f,0.0f,0.0f,0.01f };
	Math::Vector::Vector3 scaleVelocity = {};
	bool isDraw_ = false;
};

namespace Engine::Particle {

	using namespace Engine::Buffer;

	/// <summary>
	/// Mode　2dor3d
	/// </summary>
	enum DrawMode
	{
		mode_3d,
		mode_2d,
	};

	/// <summary>
	/// パーティクル本体
	/// </summary>
	class GpuParticle
	{
	public:
		GpuParticle() {};
		~GpuParticle() {};

		/// <summary>
		/// 作成
		/// </summary>
		/// <param name="合計数"></param>
		/// <param name="名前"></param>
		void Create(const size_t kNum, string Name, uint32_t modelHandle = 0);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 表示
		/// </summary>
		void Draw();

		/// <summary>
		/// 更新処理前後関係のバリア
		/// </summary>
		void CallBarrier();

		/// <summary>
		/// 使わない　command積む
		/// </summary>
		/// <param name="rootParamIndex"></param>
		void CallUavRootparam(uint32_t rootParamIndex);

		/// <summary>
		/// パラメーターを初期化
		/// </summary>
		void Clear();

#pragma region Set
		void SetTexhandle(uint32_t texHandle) { texHandle_ = texHandle; }
		void SetMode(SpriteMode belnd) { blend_ = belnd; }
		void SetDrawMode(DrawMode mode) { drawMode_ = mode; }
		void Set2dSize(const Math::Vector::Vector2& size) { size_ = size; }
		void SetNoiseTexHandle(uint32_t handle) { noiseTexHandle_ = handle; }
		void SetPos(const Math::Vector::Vector2& pos) { pos_ = pos; }

#pragma endregion

#pragma region Get
		string GetName() { return name_; }
		uint32_t GetNum() { return uint32_t(particleNum_); }

		BufferResource<uint32_t>* GetFreeListIndexBuf() { return freeListIndexBuf_.get(); }
		BufferResource<uint32_t>* GetFreeListBuf() { return freeListBuf_.get(); }
#pragma endregion

	private:

		size_t particleMin = 1024;
		size_t particleNum_ = 0;
		string name_ = "";
		uint32_t mulNum = 1;
		int vertexNum_ = 4;
		int indexNum_ = 6;
		unique_ptr<BufferResource<Particle::System::StructData::ParticleVertexData>>vertexBuf_ = nullptr;
		vector<Particle::System::StructData::ParticleVertexData>vertexParam_;
		unique_ptr<BufferResource<uint32_t>>indexBuf_ = nullptr;
		vector<uint32_t>indexParam_;

		unique_ptr<BufferResource<Particle::System::StructData::EffectData>>effectDataBuf_ = nullptr;
		Particle::System::StructData::EffectData effectParam_ = {};

		unique_ptr<BufferResource<ParticleCS>>writeParticleBuf_ = nullptr;
		vector<ParticleCS>writeParticleParam_;

		//フリーリストのインデックス
		unique_ptr<BufferResource<uint32_t>>freeListIndexBuf_ = nullptr;
		vector<uint32_t>freeListIndex_;

		//List
		unique_ptr<BufferResource<uint32_t>>freeListBuf_ = nullptr;
		vector<uint32_t>freeList_;

		uint32_t texHandle_ = 1;
		uint32_t noiseTexHandle_ = 1;
		uint32_t modelHandle_ = 0;
		SModelData modelData_{};


		SpriteMode  blend_ = BlendNone;
		DrawMode drawMode_ = DrawMode::mode_3d;

		//2d
		Math::Vector::Vector2 pos_ = {};
		Math::Vector::Vector2 size_ = {};

	};

};