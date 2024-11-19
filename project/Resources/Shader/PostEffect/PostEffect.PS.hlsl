#include "PostEffect.hlsli"

Texture2D<float32_t4> gTexture : register(t0);
Texture2D<float32_t> gDepthTexture : register(t1);
Texture2D<float32_t4> gColorTexture : register(t3);

SamplerState gSamplerLiner : register(s0);
SamplerState gSamplerPoint : register(s1);


ConstantBuffer<PostEffectParam> gPostEffectParam : register(b1);
ConstantBuffer<PostEffectBlurParam> gPostEffectBlurParam : register(b2);
ConstantBuffer<PostEffectAdjustedColor> gPostEffectAdjustedColorParam_ : register(b3);
ConstantBuffer<DirectionLightParam> gDirectionParam : register(b4);

ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b7);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float32_t4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gPostEffectParam.uvMatrix);
    float32_t4 textureColor = gTexture.Sample(gSamplerLiner, transformedUV.xy);

    float32_t4 resultColor = textureColor;
     
    //uvSize
    uint32_t width, height;
    gTexture.GetDimensions(width, height);
    float32_t2 uvStepSize = float32_t2(rcp(width), rcp(height));
    
    float32_t2 difference = float32_t2(0.0f, 0.0f);
    
    for (int32_t x = 0; x < 3; ++x)
    {
        for (int32_t y = 0; y < 3; ++y)
        {
            float32_t2 texcoord = transformedUV.xy + kIndex3x3[x][y] * uvStepSize;
             //view変換
            float32_t ndcDepth = gDepthTexture.Sample(gSamplerPoint, texcoord);

            float32_t4 viewSpace = mul(float32_t4(0.0f,0.0f, ndcDepth, 1.0f), gTransformationViewMatrix.InverseProj);
            float32_t view = viewSpace.z * rcp(viewSpace.w);
 
            difference.x += view * kPrewittHorizontalKernel[x][y];
            difference.y += view * kPrewittVerticelKernel[x][y];
        }
    }

    float32_t weight = length(difference*0.1f);
    weight = saturate(weight);
    //resultColor.rgb = resultColor.rgb * (1.0f - weight);
    
    //グレースケール
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
        vignette = 1-saturate(pow(vignette, gPostEffectAdjustedColorParam_.vignetteFactor));

        resultColor.rgb = lerp(resultColor.rgb, gPostEffectAdjustedColorParam_.vignetteColor.rgb, vignette);
    }
 
    output.color.rgb = resultColor.rgb;
    output.color.a = 1.0f;
  
 
    return output;
}