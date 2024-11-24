#pragma once
#pragma once
#include"DirectXCommon.h"

#include"../GpuParticle.h"
#include"StructGpuParticleEmitter.h"

namespace Engine::Particle {

	using namespace Engine::Buffer;

	/// <summary>
	/// パーティクルエミッター
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class ParticleEmitter
	{
	public:
		ParticleEmitter() {};
		~ParticleEmitter() {};

		/// <summary>
		/// particleをもとに作成
		/// </summary>
		/// <param name="particle"></param>
		void CreateType(unique_ptr<Particle::GpuParticle>& particle);

		/// <summary>
		/// imgui更新
		/// </summary>
		void ImGuiUpdate();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 沸かせる
		/// </summary>
		/// <param name="particle"></param>
		void Emit(unique_ptr<Particle::GpuParticle>& particle);

		/// <summary>
		/// 範囲デバック表示
		/// </summary>
		void SpownDraw();

		/// <summary>
		/// 指定のパラメータを初期化
		/// </summary>
		/// <param name="index"></param>
		void Clear(uint32_t index) { emitParam_[index] = {}; particleControl_[index] = {}; }
		
		/// <summary>
		/// すべてのパラメーターの初期化
		/// </summary>
		void AllClear();

#pragma region Get

		vector<T>& GetEmitParam() { return emitParam_; }
		vector<T>& GetWorldTransforms() { return wTs_; }
		vector<Particle::ParticleEmitControl>& GetControlParam() { return particleControl_; }

		string GetEmitName() { return name_; }
		const uint32_t GetEmitMax() { return max_; }

#pragma endregion

	private:

		/// <summary>
		/// デバック用のdrawのクラスを作成
		/// </summary>
		void CreateDebugDraw();

#pragma region imguiUpdate
		void BoxImGuiUpdate();
		void SphereImGuiUpdate();
		void CircleImGuiUpdate();
#pragma endregion

		/// <summary>
		/// 沸く間隔の更新
		/// </summary>
		/// <param name="index"></param>
		void FrequencyUpdate(size_t index);

		string name_ = "";
		static const uint32_t max_ = 32;
		uint32_t srvHandle_ = 0;

		vector<T> emitParam_;
		vector<Particle::ParticleEmitControl>particleControl_;

		unique_ptr<BufferResource<T>>emitBuf_ = nullptr;

		vector<Engine::Transform::WorldTransform>wTs_{};
		vector<unique_ptr<Primitive::LineModel>>lines_{};
	};

	template<typename T>
	inline void ParticleEmitter<T>::CreateType(unique_ptr<Particle::GpuParticle>& particle)
	{
		//各種構造体の時にwtに代入
		if constexpr (std::is_same<T, Particle::EmitType::SphereParam>::value)
		{
			name_ = particle->GetName() + "EmitSphere";
		}
		else if constexpr (std::is_same<T, Particle::EmitType::BoxParam>::value)
		{
			name_ = particle->GetName() + "EmitBox";
		}
		else if constexpr (std::is_same<T, Particle::EmitType::Circle>::value)
		{
			name_ = particle->GetName() + "EmitCircle";
		}


		emitBuf_ = make_unique<BufferResource<T>>();
		emitBuf_->CreateResource(max_);
		emitBuf_->CreateInstancingResource(max_, name_, sizeof(T));

		//emitの合計数分確保
		emitParam_.resize(max_);
		particleControl_.resize(max_);
		wTs_.resize(max_);

		for (size_t index = 0; index < max_; index++)
		{
			wTs_[index].Initialize();
		}

		//デバッグ用のモデルの線作成
#ifdef _USE_IMGUI
		CreateDebugDraw();
#endif // _USE_IMGUI

	}

	template<typename T>
	inline void ParticleEmitter<T>::ImGuiUpdate()
	{
		if constexpr (std::is_same<T, Particle::EmitType::SphereParam>::value) {
			SphereImGuiUpdate();
		}
		else if constexpr (std::is_same<T, Particle::EmitType::BoxParam>::value) {
			BoxImGuiUpdate();
		}else if constexpr (std::is_same<T, Particle::EmitType::Circle>::value) {
			CircleImGuiUpdate();
		}
	}

	template<typename T>
	inline void ParticleEmitter<T>::Update()
	{
		//時間の更新
		for (size_t index = 0; index < max_; index++)
		{
			FrequencyUpdate(index);

#ifdef _USE_IMGUI

			wTs_[index].transform.translate = emitParam_[index].translate;
			wTs_[index].transform.rotate = emitParam_[index].rotate;
			//各種構造体の時にwtに代入
			if constexpr (std::is_same<T, Particle::EmitType::SphereParam>::value)
			{
				Particle::System::UpdateSphere(lines_[index], emitParam_[index]);
			}
			else if constexpr (std::is_same<T, Particle::EmitType::BoxParam>::value)
			{
				Particle::System::UpdateBox(lines_[index], emitParam_[index]);
			}
			else if constexpr (std::is_same<T, Particle::EmitType::Circle>::value)
			{
				Particle::System::UpdateCircle(lines_[index], emitParam_[index]);
			}

			wTs_[index].UpdateMatrix();

#endif // _USE_IMGUI
		}
		emitBuf_->Map();
		emitBuf_->Setbuffer(emitParam_);
	}

	template<typename T>
	inline void ParticleEmitter<T>::Emit(unique_ptr<Particle::GpuParticle>& particle)
	{
		SPSOProperty pso = {};
		//型のパイプラインをGet
		if constexpr (std::is_same<T, Particle::EmitType::SphereParam>::value) {
			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_EMITTER, "Sphere");
		}
		else if constexpr (std::is_same<T, Particle::EmitType::BoxParam>::value) {

			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_EMITTER, "Box");
		}
		else if constexpr (std::is_same<T, Particle::EmitType::Circle>::value) {

			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_EMITTER, "Goal");
		}

		ComPtr<ID3D12GraphicsCommandList> list = Engine::Base::DX::DirectXCommon::GetInstance()->GetCommands().m_pList;

		list->SetComputeRootSignature(pso.rootSignature.Get());
		list->SetPipelineState(pso.GraphicsPipelineState.Get());

		particle->CallUavRootparam(0);
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(1, emitBuf_->GetSrvIndex());
		Engine::Utility::RunTimeCounter::GetInstance()->ComputeCommandCall(2);
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(3, particle->GetFreeListIndexBuf()->GetSrvIndex());
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(4, particle->GetFreeListBuf()->GetSrvIndex());

		list->Dispatch(1, 1, 1);
	}

	template<typename T>
	inline void ParticleEmitter<T>::SpownDraw()
	{
#ifdef _USE_IMGUI
		for (size_t index = 0; index < max_; index++)
		{
			if (particleControl_[index].useFlag_) {
				lines_[index]->SetMaterial({ 0.0f,0.0f,0.0f,1.0f });
				lines_[index]->SetWorldMat(wTs_[index].GetMat());
				lines_[index]->Draw();
			}
		}

#endif // _USE_IMGUI
	}

	template<typename T>
	inline void ParticleEmitter<T>::AllClear()
	{
		for (size_t i = 0; i < max_; i++)
		{
			emitParam_[i] = {};
			particleControl_[i] = {};
		}
	}

	template<typename T>
	inline void ParticleEmitter<T>::CreateDebugDraw()
	{
		lines_.resize(max_);
		if constexpr (std::is_same<T, Particle::EmitType::SphereParam>::value) {

			for (size_t index = 0; index < max_; index++)
			{
				string name = name_ + "DebugSphere" + to_string(index);
				Particle::System::CreateSphere(lines_[index], name);
			}
		}
		else if constexpr (std::is_same<T, Particle::EmitType::BoxParam>::value) {
			for (size_t index = 0; index < max_; index++)
			{
				string name = name_ + "DebugBox" + to_string(index);
				Particle::System::CreateBox(lines_[index], name);
			}
		}
		else if constexpr (std::is_same < T, Particle::EmitType::Circle > ::value) {
			for (size_t index = 0; index < max_; index++)
			{
				string name = name_ + "DebugCircle" + to_string(index);
				Particle::System::CreateCircle(lines_[index], name);
			}
		}
		else {

			std::string message = "None Type";
			MessageBoxA(nullptr, message.c_str(), "ParticleEmitter", 0);
			assert(0);
		}
	}
	template<typename T>
	inline void ParticleEmitter<T>::BoxImGuiUpdate()
	{
		if (ImGui::TreeNode(name_.c_str()))
		{
			for (size_t index = 0; index < max_; index++)
			{
				string paramName = to_string(index);
				ImGui::Separator();
				if (ImGui::TreeNode(paramName.c_str()))
				{
					if (ImGui::TreeNode("control"))
					{
						ImGui::Checkbox("useFlag", &particleControl_[index].useFlag_);
						ImGui::DragFloat("frequencyTime", &particleControl_[index].frequencyTime);

						ImGui::TreePop();
					}
					int count = emitParam_[index].count;
					ImGui::DragInt("spownCount", &count,1);
					emitParam_[index].count = count;
					ImGui::DragFloat3("translate", &emitParam_[index].translate.x, 0.1f);
					ImGui::DragFloat3("rotate", &emitParam_[index].rotate.x, 0.1f);
					ImGui::Separator();
					ImGui::DragFloat3("sizeMin", &emitParam_[index].sizeMin.x, 0.1f);
					ImGui::DragFloat3("sizeMax", &emitParam_[index].sizeMax.x, 0.1f);
					ImGui::Separator();
					ImGui::DragFloat3("velocityMin" ,&emitParam_[index].velocityMin.x, 0.1f);
					ImGui::DragFloat3("velocityMax", &emitParam_[index].velocityMax.x, 0.1f);
					ImGui::Separator();
					ImGui::DragFloat4("colorDecayMin", &emitParam_[index].colorDecayMin.x, 0.1f);
					ImGui::DragFloat4("colorDecayMax", &emitParam_[index].colorDecayMax.x, 0.1f);
					ImGui::Separator();
					ImGui::DragFloat3("scaleVelocityMin", &emitParam_[index].scaleVelocityMin.x, 0.1f);
					ImGui::DragFloat3("scaleVelocityMax", &emitParam_[index].scaleVelocityMax.x, 0.1f);
					ImGui::Separator();
					ImGui::DragFloat3("scaleSizeMin", &emitParam_[index].scaleSizeMin.x, 0.1f);
					ImGui::DragFloat3("scaleSizeMax", &emitParam_[index].scaleSizeMax.x, 0.1f);
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
	}

	template<typename T>
	inline void ParticleEmitter<T>::SphereImGuiUpdate()
	{
		if (ImGui::TreeNode(name_.c_str()))
		{
			for (size_t index = 0; index < max_; index++)
			{
				string paramName = to_string(index);
				if (ImGui::TreeNode(paramName.c_str()))
				{
					ImGui::DragFloat3("translate", &emitParam_[index].translate.x, 0.1f);
					ImGui::DragFloat3("rotate", &emitParam_[index].rotate.x, 0.1f);
					ImGui::DragFloat("radious", &emitParam_[index].radious, 0.1f);
					ImGui::Separator();
					wTs_[index].transform.scale = { emitParam_[index].radious,emitParam_[index].radious ,emitParam_[index].radious };
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
	}
	template<typename T>
	inline void ParticleEmitter<T>::CircleImGuiUpdate()
	{
		if (ImGui::TreeNode(name_.c_str()))
		{
			for (size_t index = 0; index < max_; index++)
			{
				string paramName = to_string(index);
				ImGui::Separator();
				if (ImGui::TreeNode(paramName.c_str()))
				{
					if (ImGui::TreeNode("control"))
					{
						ImGui::Checkbox("useFlag", &particleControl_[index].useFlag_);
						ImGui::DragFloat("frequencyTime", &particleControl_[index].frequencyTime);

						ImGui::TreePop();
					}
					int count = emitParam_[index].count;
					ImGui::DragInt("spownCount", &count, 1);
					emitParam_[index].count = count;
					ImGui::DragFloat3("translate", &emitParam_[index].translate.x, 0.1f);
					ImGui::DragFloat3("rotate", &emitParam_[index].rotate.x, 0.1f);
					ImGui::Separator();
					ImGui::DragFloat("radious", &emitParam_[index].radious, 0.1f);
					ImGui::Separator();
					ImGui::DragFloat3("velocityMin", &emitParam_[index].velocityMin.x, 0.1f);
					ImGui::DragFloat3("velocityMax", &emitParam_[index].velocityMax.x, 0.1f);
					ImGui::Separator();
					ImGui::DragFloat4("colorDecayMin", &emitParam_[index].colorDecayMin.x, 0.1f);
					ImGui::DragFloat4("colorDecayMax", &emitParam_[index].colorDecayMax.x, 0.1f);
					ImGui::Separator();
					ImGui::DragFloat3("scaleVelocityMin", &emitParam_[index].scaleVelocityMin.x, 0.1f);
					ImGui::DragFloat3("scaleVelocityMax", &emitParam_[index].scaleVelocityMax.x, 0.1f);
					ImGui::Separator();
					ImGui::DragFloat3("scaleSizeMin", &emitParam_[index].scaleSizeMin.x, 0.1f);
					ImGui::DragFloat3("scaleSizeMax", &emitParam_[index].scaleSizeMax.x, 0.1f);
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
	}
	template<typename T>
	inline void ParticleEmitter<T>::FrequencyUpdate(size_t index)
	{
		if (particleControl_[index].useFlag_)
		{
			particleControl_[index].frequency += 1.0f / 60.0f;
			if (particleControl_[index].frequency >= particleControl_[index].frequencyTime)
			{
				particleControl_[index].frequency = 0.0f;
				emitParam_[index].emit = 1;
			}
			else
			{
				emitParam_[index].emit = 0;
			}
		}
	}
}