#include "DeferredShading.hlsli"

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);

struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
};

VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    float32_t4x4 resultMatrix = gTransformationMatrix.WVP;

    float32_t4 pos = mul(input.position, resultMatrix);
   // pos= float32_t4(ComputeShadow(pos.xyz), 1);

    output.position = pos;
    output.texcoord = input.texcoord;
    return output;
}