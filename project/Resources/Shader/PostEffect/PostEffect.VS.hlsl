#include "PostEffect.hlsli"

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<DirectionLightParam> gDirectionParam : register(b5);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b6);

static const uint32_t kNumVertex = 3;

static const float32_t4 kPositions[kNumVertex] =
{
    { -1.0f, 1.0f, 0.0f, 1.0f },
    { 3.0f, 1.0f, 0.0f, 1.0f },
    { -1.0f, -3.0f, 0.0f, 1.0f}
};

static const float32_t2 kTexCoords[kNumVertex] =
{
    { 0.0f, 0.0f },
    { 2.0f, 0.0f },
    { 0.0f, 2.0f }
};

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

VertexShaderOutput main(uint32_t vertexId : SV_VertexID)
{
    VertexShaderOutput output;
 
    output.position = kPositions[vertexId];
    output.texcoord = kTexCoords[vertexId];
    return output;
}