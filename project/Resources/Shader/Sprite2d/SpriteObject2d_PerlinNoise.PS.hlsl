#include"SpriteObject2d.hlsli"
#include"../PerlinNoise/PerlineNoise.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);

Texture2D<float32_t4> gTexture : register(t0);

ConstantBuffer<PerFrame> gPerFlame : register(b1);
SamplerState gSampler : register(s0);

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    //Rand
    RandomGenerator rg;
    float32_t3 rgSeed = float32_t3(input.position.x * gMaterial.perlinNoisePos.x, input.position.y * gMaterial.perlinNoisePos.y, 0.0f);
    rg.seed = rgSeed;

    //uv
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uv);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
    //perlinNOise
    float32_t2 noisePos = input.texcoord + gMaterial.perlinNoisePos;
   
    float32_t timer = (gPerFlame.deltaTime+gPerFlame.flame);
    // Perlin ノイズのスケールとフレーム数に基づいてノイズを計算
    float32_t noise = PerlinNoise2D((noisePos.xy) * gMaterial.PerlinNoiseScale, gMaterial.perlinNoiseTimer, rg);
    noise *= gMaterial.perlinNoiseFactor;
    
    output.color.rgb = textureColor.rgb * noise;
    output.color.a = gMaterial.color.a * textureColor.a;
 
    return output;
}