#include"../MatrixFanc.hlsli"
#include"../Particle.hlsli"

RWStructuredBuffer<Particle> gParticle : register(u0);
RWStructuredBuffer<int32_t> gFreeListIndex : register(u1);
RWStructuredBuffer<int32_t> gFreeList : register(u2);

[numthreads(1024, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint32_t particleIndex = DTid.x;
    
    if (particleIndex < kParticleMax)
    {
        gParticle[particleIndex].translate += gParticle[particleIndex].velocity;
        gParticle[particleIndex].matWorld = AffineMatrix(gParticle[particleIndex].scale, gParticle[particleIndex].rotate, gParticle[particleIndex].translate);
        gParticle[particleIndex].color.a -= 0.01f;
        if (gParticle[particleIndex].color.a <= 0.0f)
        {
            gParticle[particleIndex].scale = float32_t3(0.0f, 0.0f, 0.0f);
            gParticle[particleIndex].matWorld = AffineMatrix(gParticle[particleIndex].scale, gParticle[particleIndex].rotate, gParticle[particleIndex].translate);

            int32_t freeListIndex;
            InterlockedAdd(gFreeListIndex[0], 1, freeListIndex);
            if ((freeListIndex + 1) < kParticleMax)
            {
                gFreeList[freeListIndex + 1] = particleIndex;
            }
            else
            {
                InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
            }
        }
    }
    
}