
struct VertexShaderInput
{
    float32_t4 position : POSITION0;
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