#include"../MatrixFanc.hlsli"
#include"../Particle.hlsli"

struct FieldHitBox
{
    float32_t3 translate;
    float32_t3 scale;
    float32_t3 rotate;
    
    uint32_t use;
    
    float32_t3 sizeMin;
    float32_t3 sizeMax;
    
};

static const uint32_t FildMax = 32;

StructuredBuffer<FieldHitBox> gFieldHitBox : register(t0);
RWStructuredBuffer<Particle> gParticle : register(u0);


[numthreads(256, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID, uint Gid : SV_GroupID)
{
    uint32_t index = DTid.x;
 
   // 各FieldSuctionに対して処理を行う
    for (uint32_t i = 0; i < FildMax; ++i)
    {
        // 現在のFieldSuctionが有効かどうかをチェック
        if (gFieldHitBox[i].use != 0)
        {
            // 粒子がFieldSuctionのsizeMinとsizeMaxの範囲内にあるかをチェック
            if (gParticle[index].translate.x >= gFieldHitBox[i].translate.x + gFieldHitBox[i].sizeMin.x &&
                gParticle[index].translate.x <= gFieldHitBox[i].translate.x + gFieldHitBox[i].sizeMax.x &&
                gParticle[index].translate.y >= gFieldHitBox[i].translate.y + gFieldHitBox[i].sizeMin.y &&
                gParticle[index].translate.y <= gFieldHitBox[i].translate.y + gFieldHitBox[i].sizeMax.y &&
                gParticle[index].translate.z >= gFieldHitBox[i].translate.z + gFieldHitBox[i].sizeMin.z &&
                gParticle[index].translate.z <= gFieldHitBox[i].translate.z + gFieldHitBox[i].sizeMax.z)
            {
                 float32_t3 boxCenter = gFieldHitBox[i].translate + (gFieldHitBox[i].sizeMin + gFieldHitBox[i].sizeMax) * 0.5;
                float32_t3 particleToCenter = gParticle[index].translate - boxCenter;
                float32_t3 boxHalfSize = (gFieldHitBox[i].sizeMax - gFieldHitBox[i].sizeMin) * 0.5;

                float32_t3 absParticleToCenter = abs(particleToCenter);
                float32_t3 overlap = boxHalfSize - absParticleToCenter;

                if (overlap.x < overlap.y && overlap.x < overlap.z)
                {
                    gParticle[index].velocity.x=0;
                    gParticle[index].translate.x = boxCenter.x + sign(particleToCenter.x) * boxHalfSize.x;
                }
                else if (overlap.y < overlap.x && overlap.y < overlap.z)
                {
                    gParticle[index].velocity.y=0;
                    gParticle[index].translate.y = boxCenter.y + sign(particleToCenter.y) * boxHalfSize.y;
                }
                else
                {
                    gParticle[index].velocity.z=0;
                    gParticle[index].translate.z = boxCenter.z + sign(particleToCenter.z) * boxHalfSize.z;
                }
            }
        }
    }
}