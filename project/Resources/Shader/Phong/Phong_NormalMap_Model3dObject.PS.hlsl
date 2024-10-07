#include"PhongObject3d.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b2);

StructuredBuffer<PointLight> gPointLight : register(t0);
Texture2D<float32_t4> gTexture : register(t1);
Texture2D<float32_t4> gNormalTexture : register(t2);

SamplerState gSampler : register(s0);

static float32_t3 N;

float32_t3 RimLight(float32_t3 LightDir, float3 ToEye, float rimPower, float rimIntensity, float3 LightColor)
{
    //角度
    float rim = dot(N, ToEye);
    
    rim = saturate(pow(rim, rimPower));

    float3 rimColor = rimIntensity * rim * LightColor;
    return rimColor;
}
PixelShaderOutput main(VertexShaderOutput input)
{

    PixelShaderOutput output;
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uv);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
   // float32_t4 normalColor = gNormalTexture.Sample(gSampler, input.texcoord);
    float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);

    float32_t3 pTotalSpecular = 0;
    float32_t3 pTotalDffuse = 0;
    float32_t3 pTotalRimColor = 0;
 
    //法線を行列で調整
    
    N = normalize(input.normal);
    //N = normalColor.rgb * 2.0f + N - 1.0f;
    //N = normalize(N);
    for (int32_t i = 0; i < gNowLightTotal.count; i++)
    {
		//点光源
        float32_t distance = length(gPointLight[i].position - input.worldPosition);
        float32_t factor = pow(saturate(-distance / gPointLight[i].radious + 1.0f), gPointLight[i].decay);

        float32_t3 pLightDir = normalize(input.worldPosition - gPointLight[i].position);
        float32_t3 pRefrectLight = reflect(pLightDir, N);
        float32_t3 pHalfVector = normalize(-pLightDir + toEye);

        float pNdotL = dot(N, -normalize(pLightDir));
        float pCos = pow(pNdotL * 0.5f + 0.5f, 2.0f);
        float pNdotH = dot(N, pHalfVector);
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

    float32_t4 resultColor;
    resultColor.rgb = pTotalDffuse + pTotalSpecular;
    resultColor.a = gMaterial.color.a * textureColor.a;

    float32_t grayscaleFactor = dot(resultColor.rgb, float32_t3(0.2125f, 0.7154f, 0.0721f));
    float32_t3 grayscaleColor = lerp(resultColor.rgb, float32_t3(grayscaleFactor, grayscaleFactor, grayscaleFactor), gMaterial.grayFactor);
    output.color.rgb = grayscaleColor;
    output.color.a = resultColor.a;
    
    output.dfColor = gMaterial.color * textureColor;
    output.normalColor = float32_t4(N.rgb, 1);
    output.posColor = input.position;
    return output;
}