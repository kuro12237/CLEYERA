#include"LightingObject3d.hlsli"

ConstantBuffer<Material>gMaterial :register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);
StructuredBuffer<PointLight> gPointLight : register(t0);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);
Texture2D<float32_t4>gTexture : register(t1);
SamplerState gSampler : register(s0);

float32_t3 ComputeSubsurfaceScattering(float32_t3 diffuseColor, float32_t3 normal, float32_t3 viewDir, float32_t3 lightDir)
{
    // SSSの計算に必要なパラメータ
    float32_t scatterCoefficient = 0.1; // 散乱係数
    float32_t absorptionCoefficient = 0.5; // 吸収係数
    float32_t3 scatteringColor = float32_t3(1.0, 1.0, 0.2); // 散乱の色

    float32_t scatterDistance = 0.5; // 光の伝播距離

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

PixelShaderOutput main(VertexShaderOutput input) {

	PixelShaderOutput output;

	float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
	float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);

	float32_t3 pTotalSpecular = 0;
	float32_t3 pTotalDffuse = 0;

    textureColor.rgb = ComputeGrayscale(gMaterial.grayFactor, textureColor.rgb);

	for (int32_t i = 0; i < gNowLightTotal.count; i++)
	{
		//点光源
		float32_t distance = length(gPointLight[i].position - input.worldPosition);
		float32_t factor = pow(saturate(-distance / gPointLight[i].radious + 1.0f), gPointLight[i].decay);

		float32_t3 pLightDir = normalize(input.worldPosition - gPointLight[i].position);
        float32_t3 pRefrectLight = reflect(pLightDir, normalize(input.normal));
        float32_t3 pHalfVector = normalize(-pLightDir + toEye);

        float pNdotL = dot(normalize(input.normal), -normalize(pLightDir));
		float pCos = pow(pNdotL * 0.5f + 0.5f, 2.0f);
		float pNdotH = dot(normalize(input.normal), pHalfVector);
		float pSpecularPow = pow(saturate(pNdotH), gMaterial.shininess);

		//拡散
		float32_t3 pDiffuse = gMaterial.color.rgb * textureColor.rgb * gPointLight[i].color.rgb * pCos * gPointLight[i].intensity * factor;
		//鏡面
		float32_t3 pSpecular = gPointLight[i].color.rgb * gPointLight[i].intensity * factor * pSpecularPow * float32_t3(1.0f, 1.0f, 1.0f);

		pTotalDffuse = pTotalDffuse + pDiffuse;
		pTotalSpecular = pTotalSpecular + pSpecular;
	}

    output.color.rgb = pTotalDffuse + pTotalSpecular;
	output.color.a = gMaterial.color.a * textureColor.a;

	return output;
}