#include"../Particle.hlsli"

RWStructuredBuffer<Particle> gParticle : register(u0);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
 
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);

    output.color.rgb = textureColor.rgb;
    output.color.a = 1;
    
    output.dfColor = textureColor;
    output.normalColor = textureColor;
    output.posColor = input.position;
    return output;
}