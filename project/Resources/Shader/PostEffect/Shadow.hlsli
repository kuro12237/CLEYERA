struct DirectionLightParam
{
    float32_t3 pos;
    float32_t intensity;
   
};
struct VertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
};
struct TransformationMatrix
{
    float32_t4x4 WVP;
    float32_t4x4 world;
};

struct TransformationViewMatrix
{
    float32_t4x4 view;
    float32_t4x4 projection;
    float32_t4x4 orthographic;
};

