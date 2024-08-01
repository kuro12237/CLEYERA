#include"../MatrixFanc.hlsli"
#include"../Particle.hlsli"

RWStructuredBuffer<Particle> gParticle : register(u0);

[numthreads(1024, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint32_t particleIndex = DTid.x;
    
    if (particleIndex < kParticleMax)
    {
        if (gParticle[particleIndex].color.a != 0.0f)
        {
            //gParticle[particleIndex].translate += gParticle[particleIndex].velocity;

            gParticle[particleIndex].matWorld = mul(gParticle[particleIndex].matWorld, AffineMatrix(gParticle[particleIndex].scale, gParticle[particleIndex].rotate,gParticle[particleIndex].translate));
 
        }
    }
    
}