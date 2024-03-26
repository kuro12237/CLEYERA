
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
};

struct Material
{
    float4 color;
};


struct VertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
};

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};