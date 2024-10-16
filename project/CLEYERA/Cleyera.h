#pragma once
#include"Pch.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include"ShaderManager.h"
#include"GraphicsPipelineManager.h"
#include"Model.h"
#include"ImGuiManager.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"Sprite/Sprite.h"
#include"Input.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"Light/LightingManager.h"
#include"AudioManager.h"
#include"PostEffect/PostEffect.h"
#include"Graphics/DescripterManager/RTVDescripterManager.h"
#include"Light/DirectionLIght.h"
#include"Utility/GlobalVariables/GlobalVariables.h"
#include"Utility/CameraManager/CameraManager.h"
#include"Utility/RuntimeCounter/RunTimeCounter.h"
#include"Particle/GpuParticle.h"
#include"Utility/Noise/NoiseTexture.h"
#include"Utility/SkyBox/SkyBox.h"

namespace Engine {

	/// <summary>
	/// �e�@�\�������ł܂Ƃ߂�
	/// </summary>
	class Cleyera
	{
	public:
		static Cleyera* GetInstance();

		/// <summary>
		/// ������
		/// </summary>
		static void Initialize();

		/// <summary>
		/// �I���
		/// </summary>
		static void Finalize();

		/// <summary>
		/// �t���[���̍ŏ�
		/// </summary>
		static void BeginFlame();

		/// <summary>
		/// �t���[���I���
		/// </summary>
		static void EndFlame();

	private:

	};
}
