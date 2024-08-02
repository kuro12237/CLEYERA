#include"../MatrixFanc.hlsli"
#include"../Particle.hlsli"

struct EmitCounter
{
    uint32_t count;
};
struct EmitterSphere
{
    float32_t3 translate;
    float32_t radious;
    uint32_t count;
    float32_t frequency;
    float32_t frequencyTime;
    uint32_t emit;
};

RWStructuredBuffer<Particle> gParticle : register(u0);
StructuredBuffer<EmitterSphere> gEmitterSphere : register(t0);
ConstantBuffer<PerFrame> gPerFlame : register(b0);
RWStructuredBuffer<int32_t> gFreeList : register(u1);

[numthreads(1024, 1, 1)]
void main(uint32_t3 DTid : SV_DispatchThreadID)
{
    RandomGenerator generator;
    uint32_t index = DTid.x;
    generator.seed = (DTid + gPerFlame.time) * gPerFlame.time;

    if (gEmitterSphere[0].emit != 0)
    {

        for (uint32_t countIndex = 0; countIndex < gEmitterSphere[0].count; ++countIndex)
        {
         
            int32_t particleIndex;
            //InterlockedAdd(gFreeList[0], 1, particleIndex);
            
            if (particleIndex < kParticleMax)
            {
                gParticle[countIndex].scale = float32_t3(1.0f, 1.0f, 1.0f); //generator.Generate3d()/3.0f;
                gParticle[countIndex].rotate = (float32_t3) 0;
                gParticle[countIndex].translate = generator.Generate3d();
                gParticle[countIndex].color.rgb = generator.Generate3d();
                gParticle[countIndex].color.a = 1.0f;
                gParticle[countIndex].velocity = float32_t3(0.00f, 0.0f, 0.0f);
                gParticle[countIndex].matWorld = Mat4x4Identity();
                gParticle[countIndex].isDraw = true;
            }
        }
    }
    
}