
struct PostEffectParam
{
    float32_t4x4 uvMatrix;
    float32_t2 texSize;
  
};

struct PostEffectAdjustedColor
{
    bool grayScaleFlag;
    float32_t GrayFactor;
    bool InvertFlag;
    float32_t InvertFactor;
    bool BringhtnessFlag;
    float32_t BringhtnessFactor;
    bool ContrastFlag;
    float32_t ContrastFactor;
    bool HueFlag;
    float32_t HueFactor;
};

struct PostEffectBlurParam
{
    bool UseFlag;
    float Intensity;
};

struct DirectionLightParam
{
    float32_t4x4 mat;
    float32_t3 pos;
    float32_t intensity;
    bool useFlag;
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
    float32_t3 CameraPosition;
};

struct VertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
};

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
    float32_t4 colorBoutput : SV_TARGET1;
};

