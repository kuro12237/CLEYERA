#include"DeferredShadingObject3d.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b3);
Texture2D<float4> gTexture : register(t1);
SamplerState gSampler : register(s0);

PixelShaderOutput main(WorldPositionVertexShaderOutput input)
{
    PixelShaderOutput output;

    float4 transformedUV = float4(input.texcoord, 0.0f, 1.0f);
  
    float4 WorldPos =input.position;
    WorldPos.xy = transformedUV.xy;
    output.color = WorldPos;
    return output;
}