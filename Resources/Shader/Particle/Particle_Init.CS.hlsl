#include "Particle.hlsli"
#include"MatrixFanc.hlsli"

RWStructuredBuffer<Particle> gParticle : register(u0);

[numthreads(1024, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint32_t particleIndex = DTid.x;
    if (particleIndex < kParticleMax)
    {
        gParticle[particleIndex] = (Particle) 0;
        gParticle[particleIndex].scale = float32_t3(1.0f, 1.0f, 1.0f);
        gParticle[particleIndex].matWorld = Mat4x4Identity();
        gParticle[particleIndex].color = float32_t4(1.0f, 1.0f, 1.0f, 1.0f);
        gParticle[particleIndex].velocity = float32_t3(0.0001f, 0.000f, 0.0001f);
    }
}