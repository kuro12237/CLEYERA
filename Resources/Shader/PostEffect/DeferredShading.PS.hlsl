#include"DeferredShading.hlsli"

Texture2D<float32_t4> gTexture : register(t0);
Texture2D<float32_t4> gNormalTexture : register(t1);
Texture2D<float32_t4> gPosTexture : register(t2);
Texture2D<float32_t> gDepthTexture : register(t3);
StructuredBuffer<PointLight> gPointLight : register(t4);

SamplerState gSampler : register(s0);

ConstantBuffer<Material> gMaterial : register(b1);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b3);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);
ConstantBuffer<DirectionLightParam> gDirectionLight : register(b5);

static float32_t3 N = 0.0f;
static float32_t3 DirectionLightDirection = 0.0f;
static float32_t3 toEye = 0.0f;

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float32_t4 transformedUV = (float32_t4(input.texcoord, 0.0f, 1.0f));
    float32_t4 ColorTextureColor = gTexture.Sample(gSampler, transformedUV.xy);
    float32_t4 NormalTextureColor = gNormalTexture.Sample(gSampler, transformedUV.xy);

    float32_t DepthTextureColor =gDepthTexture.Sample(gSampler, transformedUV.xy);
    
    float32_t4 wPos = float32_t4(transformedUV.xy * 2.0f - 1.0f, DepthTextureColor, 1.0f);
    wPos.xyz = mul(gTransformationViewMatrix.InverseViewProjection, wPos).xyz;
    wPos = wPos / wPos.w;
   
    float32_t3 pTotalSpecular = 0;
    float32_t3 pTotalDffuse = 0;

    for (int32_t i = 0; i < gNowLightTotal.count; i++)
    {
		//点光源
        float32_t distance = length(gPointLight[i].position - wPos.xyz);
        float32_t factor = pow(saturate(-distance / gPointLight[i].radious + 1.0f), gPointLight[i].decay);

        float32_t3 pLightDir = normalize(wPos.xyz - gPointLight[i].position);
        float32_t3 pRefrectLight = reflect(pLightDir, normalize(N));
        float32_t3 pHalfVector = normalize(-pLightDir + toEye);

        float pNdotL = dot(normalize(N), -normalize(pLightDir));
        float pCos = pow(pNdotL * 0.5f + 0.5f, 2.0f);
        float pNdotH = dot(normalize(N), pHalfVector);
        float pSpecularPow = pow(saturate(pNdotH), gMaterial.shininess);

		//拡散
        float32_t3 pDiffuse = gMaterial.color.rgb * ColorTextureColor.rgb * gPointLight[i].color.rgb * pCos * gPointLight[i].intensity * factor;
		//鏡面
        float32_t3 pSpecular = gPointLight[i].color.rgb * gPointLight[i].intensity * factor * pSpecularPow * float32_t3(1.0f, 1.0f, 1.0f);

        pTotalDffuse = pTotalDffuse + pDiffuse;
        pTotalSpecular = pTotalSpecular + pSpecular;
    }
    
    float32_t3 result = N.rgb; //pTotalDffuse + pTotalSpecular;
 
    float dsp = DepthTextureColor;
    //pow(DepthTextureColor, 200);
    float32_t3 dspColor = float32_t3(transformedUV.xy, dsp);
    //result.rgb = pow(dspColor.rgb,20);
    output.color = float4(result.rgb, 1);
    return output;
}
