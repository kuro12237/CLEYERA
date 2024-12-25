
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
    bool vignetteFlag;
    float vignetteFactor;
    float vignatteScale;
    float32_t3 vignetteColor;
    float32_t fogScale;
    float32_t fogAttenuationRate;
    float32_t fogStart;
    float32_t fogEnd;
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
    float32_t4x4 InverseVp;
    float32_t4x4 InverseProj;
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
};


static const float32_t PI = 3.1459265f;

static const float32_t2 kIndex3x3[3][3] =
{
    { { -1.0f, -1.0f }, { 0.0f, -1.0f }, { 1.0f, -1.0f } },
    { { -1.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { { -1.0f, 1.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } },
};
static const float2 kIndex5x5[5][5] =
{
    { { -2.0f, -2.0f }, { -1.0f, -2.0f }, { 0.0f, -2.0f }, { 1.0f, -2.0f }, { 2.0f, -2.0f } },
    { { -2.0f, -1.0f }, { -1.0f, -1.0f }, { 0.0f, -1.0f }, { 1.0f, -1.0f }, { 2.0f, -1.0f } },
    { { -2.0f, 0.0f }, { -1.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 2.0f, 0.0f } },
    { { -2.0f, 1.0f }, { -1.0f, 1.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 2.0f, 1.0f } },
    { { -2.0f, 2.0f }, { -1.0f, 2.0f }, { 0.0f, 2.0f }, { 1.0f, 2.0f }, { 2.0f, 2.0f } }
};
static const float32_t kPrewittHorizontalKernel[3][3] =
{
    { -1.0f / 6.0f, 0.0f, 1.0f / 6.0f },
    { -1.0f / 6.0f, 0.0f, 1.0f / 6.0f },
    { -1.0f / 6.0f, 0.0f, 1.0f / 6.0f },
};
static const float32_t kPrewittVerticelKernel[3][3] =
{
    { -1.0f / 6.0f, -1.0f / 6.0f, -1.0f / 6.0f },
    { 0.0f, 0.0f, 0.0f },
    { 1.0f / 6.0f, 1.0f / 6.0f, 1.0f / 6.0f },
};

// 5x5の水平Prewittカーネル
static const float32_t kPrewittHorizontalKernel5x5[5][5] =
{
    { -1.0f / 24.0f, -1.0f / 24.0f, 0.0f, 1.0f / 24.0f, 1.0f / 24.0f },
    { -1.0f / 12.0f, -1.0f / 12.0f, 0.0f, 1.0f / 12.0f, 1.0f / 12.0f },
    { -1.0f / 6.0f, -1.0f / 6.0f, 0.0f, 1.0f / 6.0f, 1.0f / 6.0f },
    { -1.0f / 12.0f, -1.0f / 12.0f, 0.0f, 1.0f / 12.0f, 1.0f / 12.0f },
    { -1.0f / 24.0f, -1.0f / 24.0f, 0.0f, 1.0f / 24.0f, 1.0f / 24.0f },
};

// 5x5の垂直Prewittカーネル
static const float32_t kPrewittVerticelKernel5x5[5][5] =
{
    { -1.0f / 24.0f, -1.0f / 12.0f, -1.0f / 6.0f, -1.0f / 12.0f, -1.0f / 24.0f },
    { -1.0f / 24.0f, -1.0f / 12.0f, -1.0f / 6.0f, -1.0f / 12.0f, -1.0f / 24.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 1.0f / 24.0f, 1.0f / 12.0f, 1.0f / 6.0f, 1.0f / 12.0f, 1.0f / 24.0f },
    { 1.0f / 24.0f, 1.0f / 12.0f, 1.0f / 6.0f, 1.0f / 12.0f, 1.0f / 24.0f },
};

static const float32_t2 kIndex9x9[9][9] =
{
    { { -4.0f, -4.0f }, { -3.0f, -4.0f }, { -2.0f, -4.0f }, { -1.0f, -4.0f }, { 0.0f, -4.0f }, { 1.0f, -4.0f }, { 2.0f, -4.0f }, { 3.0f, -4.0f }, { 4.0f, -4.0f } },
    { { -4.0f, -3.0f }, { -3.0f, -3.0f }, { -2.0f, -3.0f }, { -1.0f, -3.0f }, { 0.0f, -3.0f }, { 1.0f, -3.0f }, { 2.0f, -3.0f }, { 3.0f, -3.0f }, { 4.0f, -3.0f } },
    { { -4.0f, -2.0f }, { -3.0f, -2.0f }, { -2.0f, -2.0f }, { -1.0f, -2.0f }, { 0.0f, -2.0f }, { 1.0f, -2.0f }, { 2.0f, -2.0f }, { 3.0f, -2.0f }, { 4.0f, -2.0f } },
    { { -4.0f, -1.0f }, { -3.0f, -1.0f }, { -2.0f, -1.0f }, { -1.0f, -1.0f }, { 0.0f, -1.0f }, { 1.0f, -1.0f }, { 2.0f, -1.0f }, { 3.0f, -1.0f }, { 4.0f, -1.0f } },
    { { -4.0f, 0.0f }, { -3.0f, 0.0f }, { -2.0f, 0.0f }, { -1.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 2.0f, 0.0f }, { 3.0f, 0.0f }, { 4.0f, 0.0f } },
    { { -4.0f, 1.0f }, { -3.0f, 1.0f }, { -2.0f, 1.0f }, { -1.0f, 1.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 2.0f, 1.0f }, { 3.0f, 1.0f }, { 4.0f, 1.0f } },
    { { -4.0f, 2.0f }, { -3.0f, 2.0f }, { -2.0f, 2.0f }, { -1.0f, 2.0f }, { 0.0f, 2.0f }, { 1.0f, 2.0f }, { 2.0f, 2.0f }, { 3.0f, 2.0f }, { 4.0f, 2.0f } },
    { { -4.0f, 3.0f }, { -3.0f, 3.0f }, { -2.0f, 3.0f }, { -1.0f, 3.0f }, { 0.0f, 3.0f }, { 1.0f, 3.0f }, { 2.0f, 3.0f }, { 3.0f, 3.0f }, { 4.0f, 3.0f } },
    { { -4.0f, 4.0f }, { -3.0f, 4.0f }, { -2.0f, 4.0f }, { -1.0f, 4.0f }, { 0.0f, 4.0f }, { 1.0f, 4.0f }, { 2.0f, 4.0f }, { 3.0f, 4.0f }, { 4.0f, 4.0f } },
};

//ガウシアン
float gauss(float x, float y, float sigma)
{
    float exponent = -(x * x + y * y) * rcp(2.0f * sigma * sigma);
    float denominator = 2.0f * PI * sigma * sigma;
    
    return exp(exponent) * rcp(denominator);
}
float32_t Luminance(float32_t3 v)
{
    return dot(v, float32_t3(0.2125f, 0.714f, 0.0721f));

}