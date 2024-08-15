#include"spriteObject3d.hlsli"

struct TransformationMatrix {
	float32_t4x4 WVP;
};
ConstantBuffer<TransformationMatrix > gTransformationMatrix  : register(b0);

struct TransformationViewMatrix {
	float32_t4x4 view;
	float32_t4x4 projection;
	float32_t4x4 orthographic;
	
};
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);

struct VertexShaderInput {
	float32_t4 position : POSITION0;
	float32_t2 texcoord : TEXCOORD0;
};

VertexShaderOutput main(VertexShaderInput input) {
	VertexShaderOutput output;
	float32_t4x4 resultMatrix;
	
	float32_t4x4 CameraMatrix = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
	resultMatrix = mul(gTransformationMatrix.WVP,CameraMatrix);

	output.position = mul(input.position, resultMatrix);
	output.texcoord = input.texcoord;
	return output;
}