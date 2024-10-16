#pragma once
#include"BufferResources.h"
#include"DirectXCommon.h"
#include"Matrix/MatrixTransform.h"
struct SDirectionLight
{
	Math::Vector::Vector3 pos;
	float intensity;
	bool useFlag;
};

namespace Engine::Light
{
	using namespace Engine::Buffer;

	class DirectionalLight
	{
	public:


		static DirectionalLight* GetInstance();

		static void  Initialize();

		static void Update();

		static SDirectionLight GetLight() { return DirectionalLight::GetInstance()->light; }
#pragma region Set

		static void UseLIght(const bool& flag) { DirectionalLight::GetInstance()->light.useFlag = flag; }

		static void SetIntensity(const float& i) { DirectionalLight::GetInstance()->light.intensity = i; }

		static void SetPos(Math::Vector::Vector3 p) { DirectionalLight::GetInstance()->light.pos = p; }

#pragma endregion

		/// <summary>
		/// 使用しない
		/// </summary>
		static void CommandCall(UINT n);

	private:

		unique_ptr<BufferResource<SDirectionLight>>buffer_ = nullptr;

		SDirectionLight light = {};
		Math::Matrix::Matrix4x4 worldMat_ = {};
		Math::Matrix::Matrix4x4 viewMat_ = {};

		//Singleton
		DirectionalLight() = default;
		~DirectionalLight() = default;

		DirectionalLight(const DirectionalLight&) = delete;
		const  DirectionalLight& operator=(const DirectionalLight&) = delete;
	};
}