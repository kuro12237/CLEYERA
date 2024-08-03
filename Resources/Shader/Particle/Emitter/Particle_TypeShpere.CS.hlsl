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

float32_t3 RandomInUnitSphere(RandomGenerator generator)
{
    float32_t3 uvw = generator.Generate3d();
    
    float32_t theta = uvw.x * 2.0f * kPI_f;
    float32_t phi = acos(2.0f * uvw .y- 1.0f);
    float32_t r = pow(uvw.z, 1.0f / 3.0f); 
    float32_t sinTheta = sin(theta);
    float32_t cosTheta = cos(theta);
    float32_t sinPhi = sin(phi);
    float32_t cosPhi = cos(phi);
    float32_t3 pos = float32_t3(r * sinPhi * cosTheta, r * sinPhi * sinTheta, r * cosPhi);
    return pos;
}
RWStructuredBuffer<Particle> gParticle : register(u0);
StructuredBuffer<EmitterSphere> gEmitterSphere : register(t0);
ConstantBuffer<PerFrame> gPerFlame : register(b0);
RWStructuredBuffer<int32_t> gFreeList : register(u1);

[numthreads(1, 1, 1)]
void main(uint32_t3 DTid : SV_DispatchThreadID)
{
    RandomGenerator generator;
    generator.seed = (DTid + gPerFlame.deltaTime) * gPerFlame.deltaTime;
  
    if (gEmitterSphere[0].emit != 0)
    {

        for (uint32_t countIndex = 0; countIndex < gEmitterSphere[0].count; ++countIndex)
        {
            int32_t particleIndex;
            InterlockedAdd(gFreeList[0], 1, particleIndex);
            if (particleIndex < kParticleMax)
            {
                float32_t3 randomPoint = RandomInUnitSphere(generator);
                gParticle[particleIndex].scale = float32_t3(1.0f, 1.0f, 1.0f);
                gParticle[particleIndex].rotate = float32_t3(0.0f, 0.0f, 0.0f);
                gParticle[particleIndex].translate =  float32_t3(randomPoint * gEmitterSphere[0].radious);
                gParticle[particleIndex].color.rgb = generator.Generate3d();
                gParticle[particleIndex].color.a = 1.0f;
                gParticle[particleIndex].velocity = float32_t3(0.01f, 0.0f, 0.0f);
                gParticle[particleIndex].matWorld = Mat4x4Identity();
                gParticle[particleIndex].isDraw = true;
            }
        }
    }
    
}