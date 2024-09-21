#include"../Random/RandomGenerator.hlsli"

struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
};

struct VertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
    uint32_t instanceId : INSTANCEID0;
};

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};
struct TransformationViewMatrix
{
    float32_t4x4 view;
    float32_t4x4 projection;
    float32_t4x4 orthographic;
    float32_t4x4 InverseVp;
    float32_t4x4 InverseProj;
    float32_t3 CameraPosition;
};

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
    float32_t4 colorDecay;
    float32_t3 scaleVelocity;
    bool isDraw;
};

struct PerFrame
{
    float32_t flame;
    int32_t deltaTime;
};

static const uint32_t kParticleMax = 1024;

static const float kPI_f = 3.14159265358979323846f;

