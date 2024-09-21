#include"SpriteObject2d.hlsli"
#include"../PerlinNoise/PerlineNoise.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);

Texture2D<float32_t4> gTexture : register(t0);

SamplerState gSampler : register(s0);

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uv);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
    RandomGenerator rg;
    rg.seed = float3(input.position.x, input.position.y, 0.0); // èâä˙âª

    float scale = 2.0f;
    float noise = PerlinNoise2D(transformedUV.xy * scale,rg);

    float32_t4 color = float32_t4(noise, noise, noise, 1.0);
    output.color.rgb = color.rgb;
    output.color.a = gMaterial.color.a * textureColor.a;
 
    return output;
}