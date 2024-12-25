#pragma once
#include"StructParticleField.h"
#include"BufferResources.h"

namespace Engine::Particle {

	using namespace Engine::Buffer;

	/// <summary>
	/// フィールドクラス
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class ParticleField
	{
	public:
		ParticleField() {};
		~ParticleField() {};

		/// <summary>
		/// フィールドの名前入れてBuffer作成
		/// </summary>
		/// <param name="name"></param>
		void CreateType(string name);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 実行処理
		/// </summary>
		/// <param name="処理をかけるパーティクル"></param>
		void Dispach(Particle::GpuParticle* particle);

		/// <summary>
		/// imgui更新
		/// </summary>
		void ImGuiUpdate();

		/// <summary>
		/// フィールドデバッグ表示
		/// </summary>
		void FieldDraw();

		/// <summary>
		/// パラメーターを初期化
		/// </summary>
		void AllClear();

#pragma region Get
		T& GetParam(uint32_t index) { return param_[index]; }
#pragma endregion

	private:

		static const uint32_t max_ = 32;
		uint32_t srvHandle_ = 0;

		string name_ = "";
		vector<T>param_;
		unique_ptr<BufferResource<T>>buf_ = nullptr;
	};

	template<typename T>
	inline void ParticleField<T>::CreateType(string name)
	{
		name_ = name;
		param_.resize(max_);
		buf_ = make_unique<BufferResource<T>>();
		buf_->CreateResource(max_);
		buf_->CreateInstancingResource(max_, name_, sizeof(T));
	}

	template<typename T>
	inline void ParticleField<T>::Update()
	{
		buf_->Map();
		buf_->Setbuffer(param_);
	}

	template<typename T>
	inline void ParticleField<T>::Dispach(Particle::GpuParticle* particle)
	{
		SPSOProperty pso;
		if constexpr (std::is_same<T, Particle::FieldType::FieldSuction>::value)
		{
			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_FIELD, "Suction");
		}

		if constexpr (std::is_same<T, Particle::FieldType::FieldGravity>::value)
		{
			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_FIELD, "Gravity");
		}
		if constexpr (std::is_same<T, Particle::FieldType::FieldHitBox>::value)
		{
			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_FIELD, "HitBox");
		}
		ComPtr<ID3D12GraphicsCommandList> list = Engine::Base::DX::DirectXCommon::GetInstance()->GetCommands().m_pList;

		list->SetComputeRootSignature(pso.rootSignature.Get());
		list->SetPipelineState(pso.GraphicsPipelineState.Get());

		particle->CallUavRootparam(0);
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(1, buf_->GetSrvIndex());

		UINT dispach = UINT(particle->GetNum() / 256);
		list->Dispatch(dispach, 1, 1);
	}

	template<typename T>
	inline void ParticleField<T>::ImGuiUpdate()
	{
#ifdef _USE_IMGUI

		if constexpr (std::is_same<T, Particle::FieldType::FieldSuction>::value)
		{
			if (ImGui::TreeNode(name_.c_str()))
			{
				for (size_t index = 0; index < max_; index++)
				{
					string paramName = to_string(index);
					ImGui::Separator();
					if (ImGui::TreeNode(paramName.c_str()))
					{
						ImGui::DragFloat3("translate", &param_[index].translate.x, 0.1f);
						ImGui::DragFloat3("rotate", &param_[index].rotate.x, 0.1f);
						ImGui::DragInt("use", &param_[index].use, 1);

						ImGui::DragFloat3("sizeMin", &param_[index].sizeMin.x, 0.1f);
						ImGui::DragFloat3("sizeMax", &param_[index].sizeMax.x, 0.1f);
						ImGui::DragFloat("power", &param_[index].suctionPower, 0.1f);
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
		}
		if constexpr (std::is_same<T, Particle::FieldType::FieldGravity>::value)
		{
			if (ImGui::TreeNode(name_.c_str()))
			{
				for (size_t index = 0; index < max_; index++)
				{
					string paramName = to_string(index);
					ImGui::Separator();
					if (ImGui::TreeNode(paramName.c_str()))
					{
						ImGui::DragFloat3("translate", &param_[index].translate.x, 0.1f);
						ImGui::DragFloat3("rotate", &param_[index].rotate.x, 0.1f);
						ImGui::DragInt("use", &param_[index].use, 1);

						ImGui::DragFloat3("sizeMin", &param_[index].sizeMin.x, 0.1f);
						ImGui::DragFloat3("sizeMax", &param_[index].sizeMax.x, 0.1f);
						ImGui::DragFloat("gravity", &param_[index].gravity, 0.1f);
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
		}

		if constexpr (std::is_same<T, Particle::FieldType::FieldHitBox>::value)
		{
			if (ImGui::TreeNode(name_.c_str()))
			{
				for (size_t index = 0; index < max_; index++)
				{
					string paramName = to_string(index);
					ImGui::Separator();
					if (ImGui::TreeNode(paramName.c_str()))
					{
						ImGui::DragFloat3("translate", &param_[index].translate.x, 0.1f);
						ImGui::DragFloat3("rotate", &param_[index].rotate.x, 0.1f);
						ImGui::DragInt("use", &param_[index].use, 1);

						ImGui::DragFloat3("sizeMin", &param_[index].sizeMin.x, 0.1f);
						ImGui::DragFloat3("sizeMax", &param_[index].sizeMax.x, 0.1f);
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
		}
#endif // _USE_IMGUI

	}

	template<typename T>
	inline void ParticleField<T>::FieldDraw()
	{
	}

	template<typename T>
	inline void ParticleField<T>::AllClear()
	{
		for (size_t i = 0; i < max_; i++)
		{
			param_[i] = {};
		}
	}

}