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

class Cleyera
{
public:
	Cleyera() {};
	~Cleyera() {};

	static Cleyera* GetInstance();

	static void Initialize();
	static void Finalize();

	static void BeginFlame();
	static void EndFlame();


private:

	D3DResourceLeakChecker leakCheck;
};

