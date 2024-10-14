#include"../Particle.hlsli"

struct param
{
    float dissolveMask;
    float32_t2 dissolveEdgeMinMax;
    float32_t4 dissolveEdgeColor;
};

RWStructuredBuffer<Particle> gParticle : register(u0);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b0);

Texture2D<float32_t> gNoiseTexture : register(t1);
ConstantBuffer<param> gParamerter : register(b1);

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