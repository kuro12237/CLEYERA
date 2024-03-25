#include"DeferredShadingObject3d.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b3);
Texture2D<float4> gTexture : register(t1);
SamplerState gSampler : register(s0);

PixelShaderOutput main(NormalVertexShaderOutput input)
{
    PixelShaderOutput output;
    
    float4 transformedUV = float4(input.texcoord, 0.0f, 1.0f); //mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uv);
    float4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    float3 result = normalize(input.normal.rgb + textureColor.rgb);
    output.color = float4(result.rgb , 1.0f);
    return output;
}
