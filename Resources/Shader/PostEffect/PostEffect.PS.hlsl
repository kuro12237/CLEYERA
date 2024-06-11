#include "PostEffect.hlsli"

Texture2D<float32_t4> gTexture : register(t0);
Texture2D<float32_t> gShadowTexture : register(t1);
Texture2D<float32_t4> gColorTexture : register(t3);

SamplerState gSampler : register(s0);

ConstantBuffer<PostEffectParam> gPostEffectParam : register(b1);
ConstantBuffer<PostEffectBlurParam> gPostEffectBlurParam : register(b2);
ConstantBuffer<PostEffectAdjustedColor> gPostEffectAdjustedColorParam_ : register(b3);
ConstantBuffer<DirectionLightParam> gDirectionParam : register(b4);

ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b7);

//static const float32_t2 kIndex3x3[3][3] =
//{
//    { { -1.0f, -1.0f }, { 0.0f, -1.0f }, { 1.0f, -1.0f } },
//    { { -1.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f } },
//    { { -1.0f, 1.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } },
//};
static const float32_t2 kIndex3x3[9][9] =
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
static const float32_t PI = 3.1459265f;
//ガウシアン
float gauss(float x, float y, float sigma)
{
    float exponent = -(x * x + y * y) * rcp(2.0f * sigma * sigma);
    float denominator = 2.0f * PI * sigma * sigma;
    
    return exp(exponent) * rcp(denominator);
}

PixelShaderOutput main(VertexShaderOutput input)
{

    PixelShaderOutput output;
    float32_t4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gPostEffectParam.uvMatrix);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    float32_t4 resultColor = textureColor;
    
    float32_t weight = 0.0f;
    float32_t Kernel3x3[9][9];
        
    for (int32_t kernelx = 0; kernelx < 9; ++kernelx)
    {
        for (int32_t kernely = 0; kernely < 9; ++kernely)
        {
            Kernel3x3[kernelx][kernely] = gauss(kIndex3x3[kernelx][kernely].x, kIndex3x3[kernelx][kernely].y,gPostEffectAdjustedColorParam_.gaussianSigma);
            weight += Kernel3x3[kernelx][kernely];
        }
    }
  
    uint32_t width, height;
    gTexture.GetDimensions(width, height);
    float32_t2 uvStepSize = float32_t2(rcp(width), rcp(height));
    resultColor.rgb = float32_t3(0.0f, 0.0f, 0.0f);
    resultColor.a = 1.0f;
    //畳み込み
    for (int32_t x = 0; x < 9; ++x)
    {
        for (int32_t y = 0; y < 9; ++y)
        {
            float32_t2 texcoord = input.texcoord + kIndex3x3[x][y] * uvStepSize;
            float32_t3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
            resultColor.rgb += fetchColor * Kernel3x3[x][y];

        }
    }
    resultColor.rgb *= rcp(weight);
    
   
    //彩度
    {
        float32_t grayscaleFactor = dot(resultColor.rgb, float32_t3(0.2125f, 0.7154f, 0.0721f));
        float32_t3 grayscaleColor = lerp(resultColor.rgb, float32_t3(grayscaleFactor, grayscaleFactor, grayscaleFactor), gPostEffectAdjustedColorParam_.GrayFactor);
        resultColor.rgb = grayscaleColor;
    }
    //ビネット
    if (gPostEffectAdjustedColorParam_.vignetteFlag)
    {
        float32_t2 correct = transformedUV.xy * (1.0f - transformedUV.xy);
        float32_t vignette = correct.x * correct.y * gPostEffectAdjustedColorParam_.vignatteScale;
        vignette = 1 - saturate(pow(vignette, gPostEffectAdjustedColorParam_.vignetteFactor));

        resultColor.rgb = lerp(resultColor.rgb, gPostEffectAdjustedColorParam_.vignetteColor.rgb, vignette);

    }
    
    
    output.color = float32_t4(resultColor.rgb, 1.0f);
    
    return output;
}