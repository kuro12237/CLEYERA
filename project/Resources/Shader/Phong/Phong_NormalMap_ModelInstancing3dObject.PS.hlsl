#include"PhongObject3d.hlsli"

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
    float32_t4 normalColor = gNormalTexture.Sample(gSampler, input.texcoord) * 2.0f - 1.0f;
    float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);

    float32_t3 pTotalSpecular = 0;
    float32_t3 pTotalDffuse = 0;
    float32_t3 pTotalRimColor = 0;
 
    //法線を行列で調整
    N = normalize(input.normal);
 
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
    output.dfColor = float32_t4(textureColor.rgb, 1);
    output.normalColor = float32_t4(N.rgb, 1);
    
    output.posColor = input.position;
    return output;
}