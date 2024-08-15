#include "Particle.hlsli"
#include"MatrixFanc.hlsli"

RWStructuredBuffer<Particle> gParticle : register(u0);
RWStructuredBuffer<uint32_t> gFreeListIndex : register(u1);
RWStructuredBuffer<uint32_t> gFreeList : register(u2);

[numthreads(1024, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint32_t particleIndex = DTid.x;
    
    if (particleIndex < kParticleMax)
    {

        gParticle[particleIndex] = (Particle) 0;
        gFreeList[particleIndex] = particleIndex;
        gParticle[particleIndex].scale = float32_t3(1.0f, 1.0f, 1.0f);
        gParticle[particleIndex].matWorld = Mat4x4Identity();
        gParticle[particleIndex].color = float32_t4(1.0f, 1.0f, 1.0f, 1.0f);
        gParticle[particleIndex].velocity = float32_t3(0.0f, 0.000f, 0.0f);
        gParticle[particleIndex].isDraw = false;
    }
    if (particleIndex == 0)
    {
        gFreeListIndex[0] = kParticleMax - 1;
    }
}