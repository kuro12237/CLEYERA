
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
    float32_t3 worldPosition : WORLDPOSITION0;
    float32_t4 color : COLOR0;
};

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
    float32_t4 dfColor : SV_TARGET1;
    float32_t4 normalColor : SV_TARGET2;
    float32_t4 posColor : SV_TARGET3;
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

static const uint32_t kParticleMax = 1024;