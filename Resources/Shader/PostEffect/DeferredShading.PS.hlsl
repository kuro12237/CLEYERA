#include"DeferredShading.hlsli"

Texture2D<float32_t4> gTexture : register(t0);
Texture2D<float32_t4> gNormalTexture : register(t1);
SamplerState gSampler : register(s0);

ConstantBuffer<Material> gMaterial : register(b1);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b3);
StructuredBuffer<PointLight> gPointLight : register(t3);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float32_t4 transformedUV = (float32_t4(input.texcoord, 0.0f, 1.0f));
    float32_t4 ColorTextureColor = gTexture.Sample(gSampler, transformedUV.xy);
    float32_t4 NormalTextureColor = gNormalTexture.Sample(gSampler, transformedUV.xy);

 
    float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.position.xyz);

    float32_t3 pTotalSpecular = 0;
    float32_t3 pTotalDffuse = 0;

    
	//VP
    float4x4 CameraMatrix = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);

    
    for (int32_t i = 0; i < gNowLightTotal.count; i++)
    {
        float32_t4x4 LightWorldMatrix = mul(gPointLight[i].mat, CameraMatrix);
        float32_t4 lightpos = float32_t4(gPointLight[i].position,1);
        lightpos = mul(lightpos, LightWorldMatrix);


        float32_t distance = length(lightpos.xyz - input.position.xyz);
        float32_t factor = pow(saturate(-distance / gPointLight[i].radious + 1.0f), gPointLight[i].decay);

        float32_t3 pLightDir = normalize(input.position.xyz - gPointLight[i].position);
        float32_t3 pRefrectLight = reflect(pLightDir, normalize(NormalTextureColor.rgb));
        float32_t3 pHalfVector = normalize(-pLightDir + toEye);

        float pNdotL = dot(normalize(NormalTextureColor.rgb), -normalize(pLightDir));
        float pCos = pow(pNdotL * 0.5f + 0.5f, 2.0f);
        float pNdotH = dot(normalize(NormalTextureColor.rgb), pHalfVector);
        float pSpecularPow = pow(saturate(pNdotH), 70.0f);

		//拡散
        float32_t3 pDiffuse = gMaterial.color.rgb * ColorTextureColor.rgb * gPointLight[i].color.rgb * pCos * gPointLight[i].intensity * factor;
		//鏡面
        float32_t3 pSpecular = gPointLight[i].color.rgb * gPointLight[i].intensity * factor * pSpecularPow * float32_t3(1.0f, 1.0f, 1.0f);

        pTotalDffuse = pTotalDffuse + pDiffuse;
        pTotalSpecular = pTotalSpecular + pSpecular;
    }
    output.color = float4(pTotalDffuse + pTotalSpecular,1);
    
    return output;
}
