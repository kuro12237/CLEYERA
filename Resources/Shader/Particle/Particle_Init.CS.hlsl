
struct Particle
{
    float32_t3 translate;
    float32_t3 scale;
    float32_t3 rotate;
    float32_t4x4 matWorld;
    float32_t lifeTime;
    float32_t3 velocity;
    float32_t currentTime;
    float32_t4 color;
};

static const uint32_t kParticleMax = 1024;
RWStructuredBuffer<Particle> gParticle : register(u0);

[numthreads(1024, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint32_t particleIndex = DTid.x;
    if (particleIndex < kParticleMax)
    {
        gParticle[particleIndex] = (Particle) 0;
        gParticle[particleIndex].scale = float32_t3(1.0f, 1.0f, 1.0f);
        gParticle[particleIndex].matWorld = float32_t4x4
        (
          float32_t4(1.0f, 0.0f, 0.0f, 0.0f),
          float32_t4(0.0f, 1.0f, 0.0f, 0.0f),
          float32_t4(0.0f, 0.0f, 1.0f, 0.0f),
          float32_t4(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }
}