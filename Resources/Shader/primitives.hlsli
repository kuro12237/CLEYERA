
struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    uint vertexId : SV_VertexID;
};
struct VertexShaderOutput
{
    float32_t4 position : SV_POSITION;
};

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};
struct Material
{
    float32_t4 color;
};
struct TransformationViewMatrix
{
    float32_t4x4 view;
    float32_t4x4 projection;
    float32_t4x4 orthographic;
    float32_t3 CameraPosition;
};
struct TransformationMatrix
{
    float32_t4x4 WVP;
    float32_t4x4 World;
};
struct Line
{
    float32_t3 start;
    float32_t3 end;
};