#include"../MatrixFanc.hlsli"
#include"../Particle.hlsli"

struct EmitCounter
{
    uint32_t kMax;
};
struct EmitterCircle
{
    
    float32_t3 translate;
    float32_t3 rotate;
    float32_t4x4 matWorld;
    float32_t4x4 matVPV;
    uint32_t count;
    uint32_t emit;
    float32_t radious;
    
    float32_t3 velocityMin;
    float32_t3 velocityMax;

    float32_t4 color;
    float32_t4 colorDecayMin;
    float32_t4 colorDecayMax;
    
    float32_t3 scaleVelocityMin;
    float32_t3 scaleVelocityMax;
    
    float32_t3 scaleSizeMin;
    float32_t3 scaleSizeMax;
    
};

// OBBの中でランダムな点を生成する関数
float32_t4 GenerateRandomColorDecay(EmitterCircle box, RandomGenerator generator)
{
    float32_t4 rgba;
    rgba.rgb = generator.Generate3d();
    rgba.a = generator.Generate3d().r;
    
    float32_t4 decay;
    decay.r = (box.colorDecayMin.r + rgba.r * (box.colorDecayMax.r - box.colorDecayMin.r));
    decay.g = (box.colorDecayMin.g + rgba.g * (box.colorDecayMax.g - box.colorDecayMin.g));
    decay.b = (box.colorDecayMin.b + rgba.b * (box.colorDecayMax.b - box.colorDecayMin.b));
    decay.a = (box.colorDecayMin.a + rgba.a * (box.colorDecayMax.a - box.colorDecayMin.a));

    return decay;
}

float32_t3 GenerateRandomMinMax(float32_t3 minVelocity, float32_t3 maxVelocity, RandomGenerator generator)
{
    float32_t3 uvw = generator.Generate3d();

    float32_t3 velocity;
    velocity.x = minVelocity.x + uvw.x * (maxVelocity.x - minVelocity.x);
    velocity.y = minVelocity.y + uvw.y * (maxVelocity.y - minVelocity.y);
    velocity.z = minVelocity.z + uvw.z * (maxVelocity.z - minVelocity.z);

    return velocity;
}

float2 CalculateCircularPosition(float radius, int index, int totalPoints)
{
    // 各点の間隔を計算
    float angleStep = 2.0 * 3.14159265359 / totalPoints; // 360度をラジアンで表現
    // 現在の点の角度を計算
    float theta = angleStep * index;
    // 座標を計算
    float x = radius * cos(theta);
    float y = radius * sin(theta);
    return float2(x, y);
}

ConstantBuffer<PerFrame> gPerFlame : register(b0);
StructuredBuffer<EmitterCircle> gEmitterSphere : register(t0);

RWStructuredBuffer<Particle> gParticle : register(u0);
RWStructuredBuffer<int32_t> gFreeListIndex : register(u1);
RWStructuredBuffer<int32_t> gFreeList : register(u2);

[numthreads(1024, 1, 1)]
void main(uint32_t3 DTid : SV_DispatchThreadID, uint32_t3 GTid : SV_GroupThreadID)
{
    RandomGenerator generator;
    generator.seed = (((DTid.x + 1) + gPerFlame.deltaTime) * gPerFlame.deltaTime);
  
    uint32_t index = DTid.x;

    if (gEmitterSphere[index].emit != 0)
    {
        int circleindex = 0;
        float32_t4x4 emitterRotateMat = mul(mul(RotateMatrixX(gEmitterSphere[index].rotate.x), RotateMatrixY(gEmitterSphere[index].rotate.y)), RotateMatrixZ(-gEmitterSphere[index].rotate.z));
        for (uint32_t countIndex = 0; countIndex < gEmitterSphere[index].count; ++countIndex)
        {
            int32_t freeListIndex;
            InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
    
            if (0 <= freeListIndex && freeListIndex < kParticleMax)
            {
                uint32_t particleIndex = gFreeList[freeListIndex];
                gParticle[particleIndex].scale = GenerateRandomMinMax(gEmitterSphere[index].scaleSizeMin, gEmitterSphere[index].scaleSizeMax, generator);
                gParticle[particleIndex].rotate = float32_t3(0.0f, 0.0f, 0.0f);

                float2 circularPos = CalculateCircularPosition(gEmitterSphere[index].radious, circleindex, gEmitterSphere[index].count);
                float3 localPos = float3(circularPos.x, circularPos.y, 0.0f);

                float32_t4 translate = mul(emitterRotateMat, float32_t4(localPos, 1.0f));
                gParticle[particleIndex].translate= gEmitterSphere[index].translate.xyz + translate.xyz;
                
               
                gParticle[particleIndex].color = gEmitterSphere[index].color;
                
                gParticle[particleIndex].colorDecay = GenerateRandomColorDecay(gEmitterSphere[index], generator);
             
                gParticle[particleIndex].velocity = GenerateRandomMinMax(gEmitterSphere[index].velocityMin, gEmitterSphere[index].velocityMax, generator);
                gParticle[particleIndex].scaleVelocity = GenerateRandomMinMax(gEmitterSphere[index].scaleVelocityMin, gEmitterSphere[index].scaleVelocityMax, generator);
                
                gParticle[particleIndex].matWorld = Mat4x4Identity();
                gParticle[particleIndex].isDraw = true;
                circleindex++;
            }
            else
            {
                InterlockedAdd(gFreeListIndex[0], 1);
                break;
            }
        }
    }
}