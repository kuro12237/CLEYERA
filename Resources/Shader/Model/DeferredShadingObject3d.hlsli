
struct Material
{
    float4 color;
    //float32_t4x4 uv;
};

struct TransformationMatrix
{
    float32_t4x4 WVP;
};

struct TransformationViewMatrix
{
    float32_t4x4 view;
    float32_t4x4 projection;
    float32_t4x4 orthographic;
    float32_t3 CameraPosition;
};


struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

struct ColorVertexShaderOutput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};

struct NormalVertexShaderOutput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
    float3 normal : Normal;
};
