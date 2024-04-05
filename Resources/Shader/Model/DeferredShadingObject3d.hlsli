
struct Material
{
    float32_t4 color;
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
    float32_t4 color : SV_TARGET0;
};

struct ColorVertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
};

struct NormalVertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD;
    float32_t3 normal : Normal;
    float32_t4x4 worldMatrix : WORLDMATRIX0;
};
struct WorldPositionVertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD;
    float32_t3 normal : Normal;
    float32_t4x4 worldMatrix : WORLDMATRIX0;
};

