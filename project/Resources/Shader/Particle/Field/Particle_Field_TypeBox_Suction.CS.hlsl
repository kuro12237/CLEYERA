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

   // �eFieldSuction�ɑ΂��ď������s��
    for (uint32_t i = 0; i < FildMax; ++i)
    {
        // ���݂�FieldSuction���L�����ǂ������`�F�b�N
        if (gFieldSuction[i].use != 0)
        {
            // ���q��FieldSuction��sizeMin��sizeMax�͈͓̔��ɂ��邩���`�F�b�N
            if (gParticle[index].translate.x >= gFieldSuction[i].translate.x + gFieldSuction[i].sizeMin.x &&
                gParticle[index].translate.x <= gFieldSuction[i].translate.x + gFieldSuction[i].sizeMax.x &&
                gParticle[index].translate.y >= gFieldSuction[i].translate.y + gFieldSuction[i].sizeMin.y &&
                gParticle[index].translate.y <= gFieldSuction[i].translate.y + gFieldSuction[i].sizeMax.y &&
                gParticle[index].translate.z >= gFieldSuction[i].translate.z + gFieldSuction[i].sizeMin.z &&
                gParticle[index].translate.z <= gFieldSuction[i].translate.z + gFieldSuction[i].sizeMax.z)
            {
                // �z�����ݏ����������ōs��
                // �Ⴆ�΁A���q�̑��x���z�����ݒ��S�֌������悤�ɕύX����Ȃ�
                float32_t3 suctionDirection = normalize(gFieldSuction[i].translate - gParticle[index].translate);
                gParticle[index].translate += suctionDirection * gFieldSuction[i].suctionPower;
            }
        }
    }
}