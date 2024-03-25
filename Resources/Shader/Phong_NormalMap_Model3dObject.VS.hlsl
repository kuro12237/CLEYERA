#include"LightingObject3d.hlsli"

struct TransformationMatrix
{
    float32_t4x4 WVP;
    float32_t4x4 World;
};
ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);

struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
    float32_t3 worldPosition : WORLDPOSITION0;

};

VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    float32_t4x4 resultMatrix;

    float32_t4x4 CameraMatrix = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
	//view変換
    resultMatrix = mul(gTransformationMatrix.WVP, CameraMatrix);

    output.position = mul(input.position, resultMatrix);
    output.texcoord = input.texcoord;

    output.normal = normalize(mul(input.normal, (float32_t3x3) gTransformationMatrix.World));
    output.worldPosition = mul(input.position, gTransformationMatrix.WVP).xyz;
    output.worldMatrix = resultMatrix;
    return output;
}