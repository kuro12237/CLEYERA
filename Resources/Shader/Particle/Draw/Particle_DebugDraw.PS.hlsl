#include"Particle.hlsli"

static const uint32_t kParticleMax = 1024;
RWStructuredBuffer<Particle> gParticle : register(u1);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);

    output.color.rgb = float32_t3(1,1,1);
    output.color.a = 1;
    
    output.dfColor = textureColor;
    output.normalColor = textureColor;
    output.posColor = input.position;
    return output;
}