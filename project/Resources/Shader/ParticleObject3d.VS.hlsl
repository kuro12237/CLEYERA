#include"ParticleObject3d.hlsli"

struct TransformationMatrix {
	float32_t4x4 WVP;
	float32_t4x4 world;
	float32_t4 color;
	float32_t4x4 uvTransform;
};

StructuredBuffer<TransformationMatrix > gTransformationMatrix  : register(t0);

struct VertexShaderInput {
	float32_t4 position : POSITION0;
	float32_t2 texcoord : TEXCOORD0;
	float32_t4 color : COLOR0;
};

VertexShaderOutput main(VertexShaderInput input,uint32_t instanceId : SV_InstanceID) {
	VertexShaderOutput output;

	output.position = mul(input.position, gTransformationMatrix[instanceId].WVP);
	
	float32_t4 texposition; 
	texposition.rg = input.texcoord.rg;
	texposition.b = 0;
	texposition.a = 1;

	texposition = mul(texposition, gTransformationMatrix[instanceId].uvTransform);


	output.texcoord = texposition.rg;
	output.color = gTransformationMatrix[instanceId].color;

	return output;
}

/*
VertexShaderOutput main(VertexShaderInput input,uint32_t instanceId : SV_InstanceID) {
	VertexShaderOutput output;

	output.position = mul(input.position, gTransformationMatrix[instanceId].WVP);
	float32_t4 texcoord = input.texcoord;// , gTransformationMatrix[instanceId].uvTransform;

	output.texcoord = texcoord.rg;
	output.color = gTransformationMatrix[instanceId].color;

	return output;
}
*/