[numthreads(1, 1, 1)]
#include"LightingObject3d.hlsli"

ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);
StructuredBuffer<PointLight> gPointLight : register(t1);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);

ConstantBuffer<Material>gMaterial :register(b0);
Texture2D<float32_t4>gTexture : register(t0);
SamplerState gSampler : register(s0);

void main(VertexShaderOutput input )
{
	ComputeShaderOutput output;


	float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);

	float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);

	//atten 0.5,0.6,0.0
	float32_t atten = 0;
	for (int32_t i = 0; i < gNowLightTotal.count; i++)
	{
		//点光源

		float32_t distance = length(gPointLight[i].position - input.worldPosition);
		float32_t factor = pow(saturate(-distance / gPointLight[i].radious + 1.0f), gPointLight[i].decay);


		float32_t3 pLightDirection = normalize(input.worldPosition - gPointLight[i].position);
		float32_t3 pRefrectLight = reflect(pLightDirection, normalize(input.normal));
		float32_t3 pHalfVector = normalize(-pLightDirection + toEye);


		float pNdotL = dot(normalize(input.normal), -normalize(pLightDirection));
		float pCos = pow(pNdotL * 0.5f + 0.5f, 2.0f);
		float pNdotH = dot(normalize(input.normal), pHalfVector);
		float pSpecularPow = pow(saturate(pNdotH), gMaterial.shininess);

		//拡散
		float32_t3 pDiffuse = gMaterial.color.rgb * textureColor.rgb * gPointLight[i].color.rgb * pCos * gPointLight[i].intensity * factor;
		output.pTotalDffuse = pTotalDffuse + pDiffuse;
		//鏡面
		float32_t3 pSpecular = gPointLight[i].color.rgb * gPointLight[i].intensity * factor * pSpecularPow * float32_t3(1.0f, 1.0f, 1.0f);
		output.pTotalSpecular = pTotalSpecular + pSpecular;
		output.aColor = gMaterial.color.a * textureColor.a;
	}

	return output;
}