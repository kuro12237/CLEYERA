#include"../Particle.hlsli"

RWStructuredBuffer<Particle> gParticle : register(u0);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
 
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);

    output.color.rgb = textureColor.rgb * gParticle[input.instanceId].color.rgb;
    output.color.a = textureColor.a * gParticle[input.instanceId].color.a;
    if (output.color.a == 0.0f)
    {
        discard;
    }
        return output;
}