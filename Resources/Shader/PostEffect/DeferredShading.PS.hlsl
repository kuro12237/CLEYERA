#include"DeferredShading.hlsli"

Texture2D<float32_t4> gTexture : register(t0);
Texture2D<float32_t4> gNormalTexture : register(t1);
Texture2D<float32_t> gDepthTexture : register(t2);

StructuredBuffer<PointLight> gPointLight : register(t3);

SamplerState gSampler : register(s0);

ConstantBuffer<Material> gMaterial : register(b1);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b3);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);
ConstantBuffer<DirectionLightParam> gDirectionLight : register(b5);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 transformedUV = (float32_t4(input.texcoord, 0.0f, 1.0f));
    float4 ColorTextureColor = gTexture.Sample(gSampler, transformedUV.xy);
    float4 NormalTextureColor = gNormalTexture.Sample(gSampler, transformedUV.xy);
    float DepthtextureColor = gDepthTexture.Sample(gSampler, transformedUV.xy);

    float3 toEye = normalize(normalize(DepthtextureColor) - gTransformationViewMatrix.CameraPosition);

    float3 pTotalSpecular = 0;
    float3 pTotalDffuse = 0;

    float3 DirectionalLightDirection = normalize(gDirectionLight.pos);
    float3 halfVector = normalize(DirectionalLightDirection - toEye);
    float pNdotH = dot(NormalTextureColor.rgb, halfVector);
    //// ハーフランバート反射の強度を計算
    float pCosHalf = pow(pNdotH * 0.5f + 0.5f,2.0f);
    float pSpecularPow = pow(saturate(pNdotH), 70.0f);

    //拡散
    float32_t3 pDiffuse = gMaterial.color.rgb * ColorTextureColor.rgb * pCosHalf;
    //鏡面
    float32_t3 pSpecular = float3(1,1,1) * pSpecularPow ;

    pTotalDffuse = pTotalDffuse + pDiffuse;
    pTotalSpecular = pTotalSpecular + pSpecular;

    output.color = float4(pTotalDffuse+pTotalSpecular,1);

    return output;
}
