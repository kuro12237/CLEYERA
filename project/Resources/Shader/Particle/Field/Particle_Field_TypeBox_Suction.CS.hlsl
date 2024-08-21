#include"../MatrixFanc.hlsli"
#include"../Particle.hlsli"

struct FieldSuction
{
    float32_t3 translate;
    float32_t3 scale;
    float32_t3 rotate;
    
    uint32_t use;
    
    float32_t3 sizeMin;
    float32_t3 sizeMax;
    
    float32_t suctionPower;
};

static const uint32_t FildMax = 32;

StructuredBuffer<FieldSuction> gFieldSuction : register(t0);
RWStructuredBuffer<Particle> gParticle : register(u0);


[numthreads(256, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID, uint Gid : SV_GroupID)
{
    uint32_t index = DTid.x;

   // 各FieldSuctionに対して処理を行う
    for (uint32_t i = 0; i < FildMax; ++i)
    {
        // 現在のFieldSuctionが有効かどうかをチェック
        if (gFieldSuction[i].use != 0)
        {
            // 粒子がFieldSuctionのsizeMinとsizeMaxの範囲内にあるかをチェック
            if (gParticle[index].translate.x >= gFieldSuction[i].translate.x + gFieldSuction[i].sizeMin.x &&
                gParticle[index].translate.x <= gFieldSuction[i].translate.x + gFieldSuction[i].sizeMax.x &&
                gParticle[index].translate.y >= gFieldSuction[i].translate.y + gFieldSuction[i].sizeMin.y &&
                gParticle[index].translate.y <= gFieldSuction[i].translate.y + gFieldSuction[i].sizeMax.y &&
                gParticle[index].translate.z >= gFieldSuction[i].translate.z + gFieldSuction[i].sizeMin.z &&
                gParticle[index].translate.z <= gFieldSuction[i].translate.z + gFieldSuction[i].sizeMax.z)
            {
                // 吸い込み処理をここで行う
                // 例えば、粒子の速度を吸い込み中心へ向かうように変更するなど
                float32_t3 suctionDirection = normalize(gFieldSuction[i].translate - gParticle[index].translate);
                gParticle[index].translate += suctionDirection * gFieldSuction[i].suctionPower;
            }
        }
    }
}