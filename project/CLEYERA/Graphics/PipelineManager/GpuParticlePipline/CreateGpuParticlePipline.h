#pragma once
#include"StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

/// <summary>
/// GPU�p�C�v���C���쐻�֐�
/// </summary>
class CreateGpuParticle
{
public:
	
	static SPSOProperty CreateGpuParticle_Init(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	static SPSOProperty CreateGpuParticle_NoneDraw(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);
	static SPSOProperty CreateGpuParticle_AddDraw(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);
	static SPSOProperty CreateGpuParticle_DissolveNoneDraw(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	static SPSOProperty CreateGpuParticle_Update(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	static SPSOProperty CreateGpuParticcle_Emitter_Sphere(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	static SPSOProperty CreateGpuParticcle_Emitter_Box(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	static SPSOProperty CreateGpuParticle_Field_Suction(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

private:

};
