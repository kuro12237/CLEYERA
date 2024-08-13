#include"PhongObject3d.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);

StructuredBuffer<PointLight> gPointLight : register(t0);
Texture2D<float32_t4> gTexture : register(t1);
Texture2D<float32_t4> gNormalTexture : register(t2);
Texture2D<float32_t4> gBaseTexture : register(t3);

SamplerState gSampler : register(s0);

static float32_t3 N;

static float32_t4 textureColor;
static float32_t4 baseTexColor;
static float32_t4 normalColor;

static float32_t scatterCoefficient;
static float32_t absorptionCoefficient;
static float32_t scatterDistance;

float32_t Harf_Lambert(float32_t3 normal, float32_t3 lightDir)
{
    return (dot(normal, lightDir)) * 0.5f + 0.5f;
}
float32_t3 ComputeSubsurfaceScattering(float32_t3 diffuseColor, float32_t3 viewDir, float32_t3 lightDir)
{
    float32_t3 scatteringColor = baseTexColor.rgb; 
    float32_t3 scatterVector = normalize(lightDir - viewDir);
    float32_t attenuation = 1.0f - exp(-scatterCoefficient * scatterDistance);
    //吸収
    float32_t3 absorbedColor = diffuseColor * exp(-absorptionCoefficient * scatterDistance);
    // 散乱
    float32_t3 scatteredColor = scatteringColor * attenuation;
    return float32_t3( attenuation * (absorbedColor + scatteredColor));
}

float32_t3 RimLight(float32_t3 LightDir, float32_t3 ToEye, float32_t rimPower, float32_t rimIntensity, float32_t3 LightColor)
{
    //角度
    float32_t rim = dot(N, ToEye);
    rim = saturate(pow(rim, rimPower));
    float32_t3 rimColor = rimIntensity * rim * LightColor;
    return rimColor;
}
PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

     textureColor = gTexture.Sample(gSampler, input.texcoord);
     baseTexColor = gBaseTexture.Sample(gSampler, input.texcoord);
     normalColor = gNormalTexture.Sample(gSampler, input.texcoord);
    scatterCoefficient = gMaterial.scatterCoefficient;
    absorptionCoefficient = gMaterial.absorptionCoefficient;
    scatterDistance = gMaterial.scatterDistance;

    float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);
    float32_t3 pTotalSpecular = 0;
    float32_t3 pTotalDffuse = 0;
    float32_t3 pTotalRimColor = 0;
    float32_t3 pTotalSSSColor = 0;

    //法線を行列で調整
    N = normalize(input.normal + normalize(normalColor.rgb));

    for (int32_t i = 0; i < gNowLightTotal.count; i++)
    {
		//点光源
        float32_t distance = length(gPointLight[i].position - input.worldPosition);
        float32_t factor = pow(saturate(-distance / gPointLight[i].radious + 1.0f), gPointLight[i].decay);

        float32_t3 pLightDir = normalize(input.worldPosition - gPointLight[i].position);
        float32_t3 pRefrectLight = reflect(pLightDir, normalize(N));
        float32_t3 pHalfVector = normalize(-pLightDir + toEye);

        float32_t pNdotL = dot(normalize(N), -normalize(pLightDir));
        float32_t pCos = pow(pNdotL * 0.5f + 0.5f, 2.0f);
        float32_t pNdotH = dot(normalize(N), pHalfVector);
        float32_t pSpecularPow = pow(saturate(pNdotH), gMaterial.shininess);

        float32_t Light_Intensity_factor = gPointLight[i].intensity * factor;

        //Rim
        float32_t3 RimColor = RimLight(pLightDir, toEye, 10.0f, Light_Intensity_factor, gPointLight[i].color.rgb);
        //SSS
        float32_t3 SSSColor = ComputeSubsurfaceScattering(baseTexColor.rgb, toEye, pLightDir) * Light_Intensity_factor;
		//拡散
        float32_t3 pDiffuse = gMaterial.color.rgb * textureColor.rgb * gPointLight[i].color.rgb * pCos * Light_Intensity_factor;
		//鏡面
        float32_t3 pSpecular = gPointLight[i].color.rgb * Light_Intensity_factor * pSpecularPow * float32_t3(1.0f, 1.0f, 1.0f);

        pTotalSSSColor = pTotalSSSColor + SSSColor;
        pTotalRimColor = pTotalRimColor + RimColor;
        pTotalDffuse = pTotalDffuse + pDiffuse;
        pTotalSpecular = pTotalSpecular + pSpecular;

    }

    output.color.rgb = pTotalDffuse + pTotalSpecular + pTotalSSSColor  + pTotalRimColor ;
    output.color.a = textureColor.a * gMaterial.color.a ;
    output.dfColor = float32_t4(textureColor.rgb, 1);
    output.normalColor = float32_t4(N.rgb, 1);
    output.posColor = input.position;
    return output;
}