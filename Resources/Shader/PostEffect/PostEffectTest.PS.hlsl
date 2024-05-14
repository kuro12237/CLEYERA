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

    //彩度
    {
        float32_t grayscaleFactor = dot(resultColor.rgb, float32_t3(0.2125f, 0.7154f, 0.0721f));
        float32_t3 grayscaleColor = lerp(resultColor.rgb, float32_t3(grayscaleFactor, grayscaleFactor, grayscaleFactor),gPostEffectAdjustedColorParam_.GrayFactor);
        resultColor.rgb = grayscaleColor;
    }
    //ビネット
    {
        float32_t2 correct = transformedUV.xy * (1.0f - transformedUV.xy);
        float32_t vignette = correct.x * correct.y * gPostEffectAdjustedColorParam_.vignatteScale;
        vignette = saturate(pow(vignette, gPostEffectAdjustedColorParam_.vignetteFactor));
        //resultColor.rgb *= vignette;
        //resultColor.rgb = lerp(resultColor.rgb, gPostEffectAdjustedColorParam_.vignetteColor.rgb, vignette);
        resultColor.rgb = lerp(resultColor.rgb, gPostEffectAdjustedColorParam_.vignetteColor.rgb, 1- vignette);

    }
    output.color = float32_t4(resultColor.rgb,1.0f);
    return output;
}