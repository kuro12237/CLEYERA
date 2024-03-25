#include"LightingObject3d.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);
StructuredBuffer<PointLight> gPointLight : register(t0);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);

Texture2D<float32_t4> gTexture : register(t1);
Texture2D <float32_t4> gNormalTexture:register(t2);

SamplerState gSampler : register(s0);

static float32_t3 N;

float32_t Harf_Lambert(float32_t3 normal, float32_t3 lightDir)
{
    return (dot(normal, lightDir)) * 0.5f + 0.5f;
}
float32_t3 ComputeSubsurfaceScattering(float32_t3 diffuseColor, float32_t3 normal, float32_t3 viewDir, float3 lightDir)
{
    // SSSの計算に必要なパラメータ
    float32_t scatterCoefficient = 1.0; // 散乱係数
    float32_t absorptionCoefficient = 10.9; // 吸収係数
    float32_t3 scatteringColor = float32_t3(1.0, 0.0, 0.0); // 散乱の色

    float32_t scatterDistance = 0.2; // 光の伝播距離

    float32_t3 scatterVector = normalize(lightDir - viewDir);
    float32_t attenuation = exp(-scatterCoefficient * scatterDistance);

  
    //吸収
    float32_t3 absorbedColor = diffuseColor * exp(-absorptionCoefficient * scatterDistance);

    // 散乱
    float32_t3 scatteredColor = scatteringColor * scatteringColor * (1.0 - attenuation);

    // Final
    float32_t3 sssColor = (1.0 - attenuation) * (absorbedColor + scatteredColor);

    return sssColor;
}



float32_t3 RimLight(float32_t3 LightDir, float3 ToEye, float rimPower, float rimIntensity,float3 LightColor)
{
    //角度
    float rim = dot(N,ToEye);
    
    rim = saturate(pow(rim, rimPower));

    float3 rimColor = rimIntensity * rim * LightColor;
    return rimColor;
}
PixelShaderOutput main(VertexShaderOutput input)
{

    PixelShaderOutput output;

    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    float32_t4 normalColor = gNormalTexture.Sample(gSampler, input.texcoord);
    float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);

    float32_t3 pTotalSpecular = 0;
    float32_t3 pTotalDffuse = 0;
    float32_t3 pTotalRimColor = 0;
 
    //法線を行列で調整
    N = normalize(input.normal + normalize(mul(normalColor.rgb, (float32_t3x3) input.worldMatrix)));

    for (int32_t i = 0; i < gNowLightTotal.count; i++)
    {
		//点光源
        float32_t distance = length(gPointLight[i].position - input.worldPosition);
        float32_t factor = pow(saturate(-distance / gPointLight[i].radious + 1.0f), gPointLight[i].decay);

        float32_t3 pLightDir = normalize(input.worldPosition - gPointLight[i].position);
        float32_t3 pRefrectLight = reflect(pLightDir, normalize(N));
        float32_t3 pHalfVector = normalize(-pLightDir + toEye);

        float pNdotL = dot(normalize(N), -normalize(pLightDir));
        float pCos = pow(pNdotL * 0.5f + 0.5f, 2.0f);
        float pNdotH = dot(normalize(N), pHalfVector);
        float pSpecularPow = pow(saturate(pNdotH), gMaterial.shininess);

        //リムライト
        float rim = pow(1.0 - clamp(dot(N, toEye), 0.0, 1.0), 5.0);
        float dotLE = pow(max(dot(normalize(toEye), normalize(pLightDir)), 0.0), 30.0);
        float32_t3 RimColor = gPointLight[i].color.rgb * 1.0f * rim * dotLE * factor * gPointLight[i].intensity;

		//拡散
        float32_t3 pDiffuse = gMaterial.color.rgb * textureColor.rgb * gPointLight[i].color.rgb * pCos * gPointLight[i].intensity * factor;
		//鏡面
        float32_t3 pSpecular = gPointLight[i].color.rgb * gPointLight[i].intensity * factor * pSpecularPow * float32_t3(1.0f, 1.0f, 1.0f);

        pTotalRimColor = pTotalRimColor + RimColor;
        pTotalDffuse = pTotalDffuse + pDiffuse;
        pTotalSpecular = pTotalSpecular + pSpecular;

    }

    output.color.rgb = pTotalDffuse + pTotalSpecular+pTotalRimColor; 
    output.color.a = gMaterial.color.a * textureColor.a;

    return output;
}