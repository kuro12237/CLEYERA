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
static float3 toEye = 0.0f;

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 transformedUV = (float32_t4(input.texcoord, 0.0f, 1.0f));
    float4 ColorTextureColor = gTexture.Sample(gSampler, transformedUV.xy);
    float4 NormalTextureColor = gNormalTexture.Sample(gSampler, transformedUV.xy);
    N = NormalTextureColor.rgb;
    N = normalize(N);

    float4 PosTexColor = gPosTexture.Sample(gSampler, transformedUV.xy);
    float DepthTextureColor =gDepthTexture.Sample(gSampler, transformedUV.xy);
    
    float3 pTotalDffuse = 0.0f;
    float3 pTotalSpecular = 0.0f;

    float4 wPos = float4(PosTexColor.gr,DepthTextureColor,1);

    //////座標系テスト
    //float4 uvProjection = float4(input.position.xy, 0, 1);
    //uvProjection.xy = uvProjection.xy * 2.0f - float2(1, 1);
    //wPos = (mul(float4(uvProjection.xy, DepthTextureColor, 1), gTransformationViewMatrix.InverseProjection));
    //wPos.xyz /= wPos.w;
    DirectionLightDirection = normalize(gDirectionLight.pos);
    wPos = (wPos);
    toEye = normalize(gTransformationViewMatrix.CameraPosition - wPos.xyz);
 
    //光処理下
    //Direction
    float32_t3 dLightDir = normalize(wPos.xyz - DirectionLightDirection);
    float32_t3 dRefrectLight = reflect(DirectionLightDirection, N);
    float32_t3 dHalfVector = normalize(-dLightDir + toEye);
    float32_t dNdotL = dot(N, -DirectionLightDirection);
    float32_t dCos = pow(dNdotL * 0.5f + 0.5f, 2.0f);
    float32_t dNdotH = dot(N, dHalfVector);
    float32_t dSpecularPow = pow(saturate(dNdotH), gMaterial.shininess);

    float32_t3 dDiffuse = gMaterial.color.rgb * ColorTextureColor.rgb * gDirectionLight.intensity * dCos;
    float32_t3 dSpecular = dSpecularPow * float32_t3(1.0f, 1.0f, 1.0f);

    pTotalDffuse += dDiffuse;
    pTotalSpecular += dSpecular;

    float3 result = float3(pTotalDffuse+pTotalSpecular);

    output.color =  float4(result.rgb, 1);
    return output;
}
