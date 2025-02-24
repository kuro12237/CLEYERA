#include"../MatrixFanc.hlsli"
#include"../Particle.hlsli"

RWStructuredBuffer<Particle> gParticle : register(u0);
RWStructuredBuffer<int32_t> gFreeListIndex : register(u1);
RWStructuredBuffer<int32_t> gFreeList : register(u2);

float32_t4 ColorCalc(float32_t4 color, float32_t4 decay)
{
    if (color.r >= 0.0f)
    {
        color.r -= decay.r;
    }
    if (color.g >= 0.0f)
    {
        color.g -= decay.g;
    }
    if (color.b >= 0.0f)
    {
        color.b -= decay.b;
    }
    if (color.a >= 0.0f)
    {
        color.a -= decay.a;
    }
    return color;
}

[numthreads(1024, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint32_t particleIndex = DTid.x;
    
    if (particleIndex < kParticleMax)
    {
        gParticle[particleIndex].translate += gParticle[particleIndex].velocity;
     
        gParticle[particleIndex].color = ColorCalc(gParticle[particleIndex].color, gParticle[particleIndex].colorDecay);
        
        gParticle[particleIndex].scale += gParticle[particleIndex].scaleVelocity;
        
        gParticle[particleIndex].matWorld = AffineMatrix(gParticle[particleIndex].scale, gParticle[particleIndex].rotate, gParticle[particleIndex].translate);
        
        //消滅処理
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