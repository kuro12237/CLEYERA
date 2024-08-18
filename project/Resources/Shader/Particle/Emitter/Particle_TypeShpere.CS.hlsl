#include"../MatrixFanc.hlsli"
#include"../Particle.hlsli"

struct EmitCounter
{
    uint32_t kMax;
};
struct EmitterSphere
{
    float32_t3 translate;
    float32_t3 rotate;
    float32_t4x4 matWorld;
    float32_t4x4 matVPV;
    uint32_t count;
    uint32_t emit;
    
    float32_t radious;
};

float32_t3 RandomInUnitSphere(RandomGenerator generator)
{
    float32_t3 uvw = generator.Generate3d();
    
    float32_t theta = uvw.x * 2.0f * kPI_f;
    float32_t phi = acos(2.0f * uvw.y - 1.0f);
    float32_t r = pow(uvw.z, 1.0f / 3.0f);
    float32_t sinTheta = sin(theta);
    float32_t cosTheta = cos(theta);
    float32_t sinPhi = sin(phi);
    float32_t cosPhi = cos(phi);
    float32_t3 pos = float32_t3(r * sinPhi * cosTheta, r * sinPhi * sinTheta, r * cosPhi);
    return pos;
}

ConstantBuffer<PerFrame> gPerFlame : register(b0);
StructuredBuffer<EmitterSphere> gEmitterSphere : register(t0);

RWStructuredBuffer<Particle> gParticle : register(u0);
RWStructuredBuffer<int32_t> gFreeListIndex : register(u1);
RWStructuredBuffer<int32_t> gFreeList : register(u2);

[numthreads(1024, 1, 1)]
void main(uint32_t3 DTid : SV_DispatchThreadID, uint32_t3 GTid : SV_GroupThreadID)
{
    RandomGenerator generator;
    generator.seed = (DTid+GTid + gPerFlame.deltaTime) * gPerFlame.deltaTime;
  
    uint32_t index = DTid.x;

    if (gEmitterSphere[index].emit != 0)
    {
        for (uint32_t countIndex = 0; countIndex < gEmitterSphere[index].count; ++countIndex)
        {
            int32_t freeListIndex;
            InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);

            if (0 <= freeListIndex && freeListIndex < kParticleMax)
            {
                uint32_t particleIndex = gFreeList[freeListIndex];
                float32_t3 randomPoint = RandomInUnitSphere(generator);
                gParticle[particleIndex].scale = float32_t3(1.0f, 1.0f, 1.0f);
                gParticle[particleIndex].rotate = float32_t3(0.0f, 0.0f, 0.0f);
                gParticle[particleIndex].translate = gEmitterSphere[index].translate + float32_t3(randomPoint + gEmitterSphere[index].radious);
                gParticle[particleIndex].color.rgb = generator.Generate3d();
                gParticle[particleIndex].color.a = 1.0f;
                gParticle[particleIndex].velocity = (generator.Generate3d() * 2.0f - 1.0f) * 0.1f;
                gParticle[particleIndex].velocity.y = generator.Generate3d().y * 0.1f;
                gParticle[particleIndex].velocity.z = 0.0f;
                gParticle[particleIndex].matWorld = Mat4x4Identity();
                gParticle[particleIndex].isDraw = true;
            }
            else
            {
                InterlockedAdd(gFreeListIndex[0], 1);
                break;
            }
        }
    }
}