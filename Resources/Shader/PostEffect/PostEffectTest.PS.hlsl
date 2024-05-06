#include "PostEffectTest.hlsli"

Texture2D<float32_t4> gTexture : register(t0);
Texture2D<float32_t> gShadowTexture : register(t1);
Texture2D<float32_t4> gColorTexture : register(t3);

SamplerState gSampler : register(s0);

ConstantBuffer<PostEffectParam> gPostEffectParam : register(b1);
ConstantBuffer<PostEffectBlurParam> gPostEffectBlurParam : register(b2);
ConstantBuffer<PostEffectAdjustedColor> gPostEffectAdjustedColorParam_ : register(b3);
ConstantBuffer<DirectionLightParam> gDirectionParam : register(b4);

ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b7);

PixelShaderOutput main(VertexShaderOutput input)
{

    PixelShaderOutput output;
    float32_t4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gPostEffectParam.uvMatrix);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    float32_t4 resultColor = textureColor;
    float32_t dsp = pow(gShadowTexture.Sample(gSampler, transformedUV.xy), 20);
    float32_t4 grayParam= gColorTexture.Sample(gSampler, transformedUV.xy);
    
    ////平均ぼかし
    //if (gPostEffectBlurParam.UseFlag)
    //{
    //    float2 texelSize = 1.0f / gPostEffectParam.texSize; 
    //    float4 blurredColor = 0.0f;

    //    for (int x = -1; x <= 1; ++x)
    //    {
    //        for (int y = -1; y <= 1; ++y)
    //        {
    //            float2 offset = float2(x, y) * texelSize * gPostEffectBlurParam.Intensity;
    //            blurredColor += gTexture.Sample(gSampler, transformedUV.xy + offset);
    //        }
    //    }
    //    resultColor.rgb += (blurredColor.rgb / 9.0f);
    //}
    ////色相
    //if (gPostEffectAdjustedColorParam_.HueFlag)
    //{
    //    float3 k = float3(0.57735f, 0.57735f, 0.57735f); // RGBの平均ベクトル
    //    float3 n = normalize(resultColor.rgb - k);
    //    float3 h = cross(n, float3(0.0f, 0.0f, 1.0f)); // 色相ベクトル
    //    float3 v = cross(n, h);

    //    // 色相回転行列の生成
    //    float32_t3x3 hueMatrix =
    //    {
    //        { 0.299f + 0.701f * cos(gPostEffectAdjustedColorParam_.HueFactor), 0.587f - 0.587f * cos(gPostEffectAdjustedColorParam_.HueFactor) - 0.114f * sin(gPostEffectAdjustedColorParam_.HueFactor), 0.114f + 0.886f * cos(gPostEffectAdjustedColorParam_.HueFactor) },
    //        { 0.299f + 0.701f * cos(gPostEffectAdjustedColorParam_.HueFactor - 2.09439510239f), 0.587f - 0.587f * cos(gPostEffectAdjustedColorParam_.HueFactor - 2.09439510239f) - 0.114f * sin(gPostEffectAdjustedColorParam_.HueFactor - 2.09439510239f), 0.114f + 0.886f * cos(gPostEffectAdjustedColorParam_.HueFactor - 2.09439510239f) },
    //        { 0.299f + 0.701f * cos(gPostEffectAdjustedColorParam_.HueFactor + 2.09439510239f), 0.587f - 0.587f * cos(gPostEffectAdjustedColorParam_.HueFactor + 2.09439510239f) - 0.114f * sin(gPostEffectAdjustedColorParam_.HueFactor + 2.09439510239f), 0.114f + 0.886f * cos(gPostEffectAdjustedColorParam_.HueFactor + 2.09439510239f) }
    //    };

    //    // 色相の変換
    //    resultColor.rgb = float32_t3(dot(hueMatrix[0], resultColor.rgb), dot(hueMatrix[1], resultColor.rgb), dot(hueMatrix[2], resultColor.rgb));
    //}
    //彩度
    {
        float32_t grayscaleFactor = dot(resultColor.rgb, float32_t3(0.2125f, 0.7154f, 0.0721f));
        float32_t3 grayscaleColor = lerp(resultColor.rgb, float32_t3(grayscaleFactor, grayscaleFactor, grayscaleFactor),gPostEffectAdjustedColorParam_.GrayFactor);
        resultColor.rgb = grayscaleColor;
    }

    output.color = float32_t4(resultColor.rgb,1.0f);
  
    return output;
}