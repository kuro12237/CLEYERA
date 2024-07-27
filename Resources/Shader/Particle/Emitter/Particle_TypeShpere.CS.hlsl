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

[numthreads(1024, 1, 1)]
void main(uint32_t3 DTid : SV_DispatchThreadID)
{
    RandomGenerator generator;
    uint32_t index = DTid.x;
  
    if (gEmitterSphere[index].emit != 0)
    {
        generator.seed = (DTid + gPerFlame.time) * gPerFlame.time;
        for (uint32_t countIndex = 0; countIndex < gEmitterSphere[index].count; ++countIndex)
        {
            gParticle[countIndex].scale = generator.Generate3d();
            gParticle[countIndex].translate = generator.Generate3d();
            gParticle[countIndex].color.rgb = generator.Generate3d();
            gParticle[countIndex].color.a = 1.0f;
            gParticle[countIndex].matWorld = Mat4x4Identity();
        }
    }
    
}