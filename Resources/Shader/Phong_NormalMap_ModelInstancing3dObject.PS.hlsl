#include"LightingObject3d.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);
StructuredBuffer<PointLight> gPointLight : register(t1);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);

Texture2D<float32_t4> gTexture : register(t2);
Texture2D<float32_t4> gNormalTexture : register(t3);

SamplerState gSampler : register(s0);

static float32_t3 N;

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
    N = normalize(N);
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
        float32_t3 pDiffuse = gMaterial.color.rgb*textureColor.rgb * gPointLight[i].color.rgb * pCos * gPointLight[i].intensity * factor;
		//鏡面
        float32_t3 pSpecular = gPointLight[i].color.rgb * gPointLight[i].intensity * factor * pSpecularPow * float32_t3(1.0f, 1.0f, 1.0f);

        pTotalRimColor = pTotalRimColor + RimColor;
        pTotalDffuse = pTotalDffuse + pDiffuse;
        pTotalSpecular = pTotalSpecular + pSpecular;

    }

    output.color.rgb = pTotalDffuse + pTotalSpecular;
    //+pTotalRimColor;
    output.color.a = gMaterial.color.a * textureColor.a;

    return output;
}