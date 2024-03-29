
struct TransformationMatrix
{
    float4x4 WVP;
    float4x4 world;
};

struct TransformationViewMatrix
{
    float4x4 view;
    float4x4 projection;
    float4x4 orthographic;
    float3 CameraPosition;
    float4x4 InverseProjection;
    float4x4 InverseViewProjection;
};

struct Material
{
    float4 color;
};

struct DirectionLightParam
{
    float32_t3 pos;
    float32_t intensity;
    bool useFlag;
};

struct PointLight
{
    float32_t4 color;
    float32_t3 position;
    float intensity;
    float radious;
    float decay;
};

struct NowLightTotal
{
    int32_t count;
};
struct VertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
    //float32_t3 normal : NORMAL0;
};

struct NormalVertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NOMAL0;
};

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};
