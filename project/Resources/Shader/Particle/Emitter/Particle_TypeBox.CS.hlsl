#include"../MatrixFanc.hlsli"
#include"../Particle.hlsli"

struct EmitCounter
{
    uint32_t kMax;
};
struct EmitterBox
{
    float32_t3 translate;
    float32_t3 rotate;
    uint32_t count;
    uint32_t emit;
    float32_t3 sizeMin;
    float32_t3 sizeMax;
    float32_t3 velocityMin;
    float32_t3 velocityMax;
};


// ��]�s����v�Z����֐��i�I�C���[�p����j
float32_t3 RotatePoint(float32_t3 local,  float32_t3 rotate)
{
    // ��]�s����v�Z
    float cosX = cos(rotate.x);
    float sinX = sin(rotate.x);
    float cosY = cos(rotate.y);
    float sinY = sin(rotate.y);
    float cosZ = cos(rotate.z);
    float sinZ = sin(rotate.z);

    // ��]��K�p
    float32_t3 rotated;
    rotated.x = local.
    x * cosY * cosZ + local.
    y * (cosX * sinZ + sinX * sinY * cosZ) - local.
    z * (sinX * sinZ - cosX * sinY * cosZ);
    rotated.y = -local.
    x * cosY * sinZ + local.
    y * (cosX * cosZ - sinX * sinY * sinZ) + local.
    z * (sinX * cosZ + cosX * sinY * sinZ);
    rotated.z = local.
    x * sinY + local.
    y * (-sinX * cosY) + local.
    z * (cosX * cosY);

    return rotated;
}

// OBB�̒��Ń����_���ȓ_�𐶐�����֐�
float32_t3 GenerateRandomPointInOBB(EmitterBox box, RandomGenerator generator)
{
    float32_t3 uvw = generator.Generate3d();
    
    float32_t3 localPoint;
    localPoint.x = (box.sizeMin.x + uvw.x * (box.sizeMax.x - box.sizeMin.x));
    localPoint.y = (box.sizeMin.y + uvw.y * (box.sizeMax.y - box.sizeMin.y));
    localPoint.z = box.sizeMin.z + uvw.z * (box.sizeMax.z - box.sizeMin.z);
    
    float32_t3 rotatedPoint = RotatePoint(localPoint, -box.rotate);

    return rotatedPoint;
}

float32_t3 GenerateRandomVelocity(float32_t3 minVelocity, float32_t3 maxVelocity, RandomGenerator generator)
{
    float32_t3 uvw = generator.Generate3d();

    float32_t3 velocity;
    velocity.x = minVelocity.x + uvw.x * (maxVelocity.x - minVelocity.x);
    velocity.y = minVelocity.y + uvw.y * (maxVelocity.y - minVelocity.y);
    velocity.z = minVelocity.z + uvw.z * (maxVelocity.z - minVelocity.z);

    return velocity;
}
ConstantBuffer<PerFrame> gPerFlame : register(b0);
StructuredBuffer<EmitterBox> gEmitterSphere : register(t0);

RWStructuredBuffer<Particle> gParticle : register(u0);
RWStructuredBuffer<int32_t> gFreeListIndex : register(u1);
RWStructuredBuffer<int32_t> gFreeList : register(u2);

[numthreads(1024, 1, 1)]
void main(uint32_t3 DTid : SV_DispatchThreadID, uint32_t3 GTid : SV_GroupThreadID)
{
    RandomGenerator generator;
    generator.seed = ((DTid.xxx + 1) * gPerFlame.deltaTime);
  
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
                float32_t3 randomPoint =  GenerateRandomPointInOBB(gEmitterSphere[index],generator);
                gParticle[particleIndex].scale = float32_t3(1.0f, 1.0f, 1.0f);
                gParticle[particleIndex].rotate = float32_t3(0.0f, 0.0f, 0.0f);
                gParticle[particleIndex].translate = gEmitterSphere[index].translate + float32_t3(randomPoint);
                gParticle[particleIndex].color.rgb = generator.Generate3d();
                gParticle[particleIndex].color.a = 1.0f;
                gParticle[particleIndex].velocity = GenerateRandomVelocity(gEmitterSphere[index].velocityMin, gEmitterSphere[index].velocityMax, generator);
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