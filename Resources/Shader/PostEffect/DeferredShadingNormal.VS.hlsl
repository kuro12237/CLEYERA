#include "DeferredShading.hlsli"

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);

struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
};

NormalVertexShaderOutput main(VertexShaderInput input)
{
    NormalVertexShaderOutput output;
    float32_t4x4 resultMatrix = gTransformationMatrix.WVP;

    float32_t4 pos = mul(input.position, resultMatrix);

    output.position = pos;
    output.normal = input.normal;
    output.texcoord = input.texcoord;
    return output;
}