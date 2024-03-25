#include "PostEffectTest.hlsli"



ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<DirectionLightParam> gDirectionParam : register(b5);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b6);

struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
};


float32_t3 ComputeShadow(float32_t3 worldPosition)
{
    float32_t4x4 LightVP = mul(gDirectionParam.mat, gTransformationViewMatrix.projection);
    float32_t4 shadowPos = mul(float32_t4(worldPosition, 1.0), LightVP);
    return shadowPos.xyz;
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