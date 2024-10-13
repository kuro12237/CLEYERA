#include"SpriteObject2d.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);

Texture2D<float32_t4> gTexture : register(t0);
Texture2D<float32_t> gNoiseTex : register(t1);

SamplerState gSampler : register(s0);

struct PixelShaderOutput
{

    float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{

    PixelShaderOutput output;
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uv);
    
    float32_t4 noiseTransformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.noiseUvTransform);
    
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
    float32_t mask = gNoiseTex.Sample(gSampler, noiseTransformedUV.xy);
   
    if (mask <= gMaterial.dissolveMask)
    {
        discard;
    }
    
      // エッジカラーを計算して適用
    float32_t min = gMaterial.dissolveMask + gMaterial.dissolveEdgeMinMax.x;
    float32_t max = gMaterial.dissolveMask + gMaterial.dissolveEdgeMinMax.y;
 
    float32_t edge = 1.0f - smoothstep(min, max, mask);
    textureColor.rgb += edge * gMaterial.dissolveEdgeColor.rgb;
  
    output.color.rgb = gMaterial.color.rgb * textureColor.rgb;
    output.color.a = gMaterial.color.a * textureColor.a;

    return output;
}