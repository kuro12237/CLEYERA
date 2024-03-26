#include"DeferredShading.hlsli"

Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

ConstantBuffer<Material> gMaterial : register(b1);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b3);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float32_t4 transformedUV = (float32_t4(input.texcoord, 0.0f, 1.0f));
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    float32_t4 resultColor = textureColor;

    output.color = resultColor;
    return output;
}
